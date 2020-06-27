#ifndef RELAYER_H_
#define RELAYER_H_
enum{
    STATE_RUNNING=1,
    STATE_CANCELED,
    STATE_OVER
};
struct rel_stat_st
{
    int state;
    int fd1;
    int fd2;
    //struct timerval start, end;
    //int count12, count21;//fd1 and fd2 communication bytes
};
int rel_addjob(int fd1, int fd2);
/*
 *return >=0            success, return current task ID
 *       == -EINVAL     fail, illegal arg
 *       == -ENOSPC     fail, task array is full
 *       == -ENOMEM     fail, malloc error
 * **********/
//int rel_canceljob(int id);
/*
 *return   ==0           success, task is canceled successfully
 *         == -EINBAL    fail, illegal arg
 *         == -EBUFY     fail, task was canceled before
 **/

//int rel_waitjob(int id, struct rel_stat_st*);
/***
 *return ==0          success, task is terminated
 *       == _EINVAL   fail, illegal arg
 *
 *
 ***/

 //int rel_statjob(int id, struct rel_stat_st*);
 /*
  *return ==0        success, task is exit
  *       ==-EINVAL  fail, illegal para
  *
  *
  */

#endif
