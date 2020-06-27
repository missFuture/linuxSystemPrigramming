#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include "relayer.h"
#define REL_JOBMAX 10000

#define BUFSIZE 1024
static int len; 
enum
{
    STATE_R,
    STATE_W,
    STATE_Ex,
    STATE_T
};
struct rel_fsm_st
{
    int state;
    int sfd;
    int dfd;
    char buf[BUFSIZE];
    int len;
    int pos;
    char *errorstr;
    int64_t count;
};

struct rel_job_st
{
    int fd1;
    int fd2;
    int job_state;
    struct rel_fsm_st fsm12;
    struct rel_fsm_st fsm21;
    int fd1_save;
    int fd2_save;

};

static struct rel_job_st* rel_job[REL_JOBMAX];
static pthread_mutex_t mut_rel_job = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t init_once = PTHREAD_ONCE_INIT;
static void fsm_driver(struct rel_fsm_st *fsm)
{
    int ret = 0;
    switch(fsm->state)
    {
        case STATE_R:
            fsm->len = read(fsm->sfd, fsm->buf + fsm->pos, BUFSIZE);//read from sfd
            if(fsm->len == 0)
                fsm->state = STATE_T;
            else if(fsm->len < 0 )
            {
                if(errno == EAGAIN)
                    fsm->state = STATE_R;
                else
                {
                    fsm->state = STATE_Ex;
                    fsm->errorstr = "read()";
                }
            }
            else
                fsm->state = STATE_W;
            break;

        case STATE_W:
            ret = write(fsm->dfd, fsm->buf + fsm->pos, fsm->len);
            if(ret < 0)
            {
                if(errno == EAGAIN)
                    fsm->state = STATE_W;
                else
                {
                    fsm->state = STATE_Ex;
                    fsm->errorstr = "write()";
                }
            }
            else
            {
                fsm->pos += ret;
                fsm->len -= ret;
                if(fsm->len == 0)// len bytes have been finished
                    fsm->state = STATE_R;
                else
                    fsm->state = STATE_W;
            }
            break;

        case STATE_Ex:
            perror(fsm->errorstr);
            fsm->state = STATE_T;
            break;

        case STATE_T:
            /*do sth*/
            break;

        default:
            /*do sth*/
            abort();
            break;
    }
}
static void* thr_relayer(void*p)
{

    while(1)
    {
        pthread_mutex_lock(&mut_rel_job);
        for(int i = 0 ; i  < REL_JOBMAX; i++)
        {
            if(rel_job[i] != NULL)
            {
                if(rel_job[i]->job_state == STATE_RUNNING)
                {
                    fsm_driver(&rel_job[i]->fsm12);
                    fsm_driver(&rel_job[i]->fsm21);
                    if(rel_job[i]->fsm12.state == STATE_T && rel_job[i]->fsm21.state == STATE_T)
                        rel_job[i]->job_state = STATE_OVER;
                }
            }
            //sleep(1);
            //printf("fsm12 state:%d\n", rel_job[0]->fsm12.state);
            //printf("fsm21 state:%d\n", rel_job[0]->fsm21.state);
            //printf("job state:%d\n", rel_job[0]->job_state);
        }
        pthread_mutex_unlock(&mut_rel_job);
    }
}
//unload
static void module_load(void)
{
    pthread_t tid_relayer;
    int err;
    err = pthread_create(&tid_relayer, NULL, thr_relayer, NULL);
    if(err)
    {
        fprintf(stderr, "pthread_create:s%\n", strerror(err));
        exit(1);
    }
    printf("load successfully\n");

}
static int get_free_pos_unlocked()
{
    for(int i = 0 ;  i < REL_JOBMAX; i++)
    {
        if(rel_job[i] == NULL)
            return i;
    }
    return -1;
}
int rel_addjob(int fd1, int fd2)
{
   struct rel_job_st *me;
   int pos = 0;
   puts("begin!");
   pthread_once(&init_once, module_load);
   puts("end!");
   me = malloc(sizeof(*me));
   if(me == NULL)
       return -ENOMEM;
   me->fd1 =fd1;
   me->fd2 =fd2;
   me->job_state = STATE_RUNNING;
   me->fd1_save = fcntl(me->fd1, F_GETFL); 
   fcntl(me->fd1, F_SETFL, me->fd1 | O_NONBLOCK);
   me->fd2_save = fcntl(me->fd2, F_GETFL);
   fcntl(me->fd2, F_SETFL, me->fd2 | O_NONBLOCK);
   me->fsm12.sfd = me->fd1;
   me->fsm12.dfd = me->fd2;
   me->fsm12.pos = 0;
   me->fsm12.state = STATE_R;
   
   me->fsm21.sfd = me->fd2;
   me->fsm21.dfd = me->fd1;
   me->fsm21.pos = 0;
   me->fsm21.state = STATE_R;

   pthread_mutex_lock(&mut_rel_job);
   pos = get_free_pos_unlocked();
   if(pos < 0)
   {
       pthread_mutex_unlock(&mut_rel_job);
       fcntl(me->fd1, me->fd1_save);
       fcntl(me->fd2, me->fd2_save);
       free(me);
       return -ENOSPC;
   }

   rel_job[pos] = me;
   printf("current free space:%d\n", pos);
   pthread_mutex_unlock(&mut_rel_job);
   return pos;
}
/*
#if 0
int rel_canceljob(int id)
{

}

int rel_waitjob(int id, struct rel_stat_st*)
{

}

int rel_statjob(int id, struct rel_stat_st*)
{

}
#endif
*/
