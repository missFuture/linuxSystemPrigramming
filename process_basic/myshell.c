/**********************************************************************
 *Function:parse
 *Description:use glob to prase command
 *Input:line, input command, for example ls -l
 *Output:run command
 *
 *
 *
 *
 *********************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <glob.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DELIMS " \t\n"
struct cmd_st
{
    glob_t globres;
};
static void prompt(void)
{
    printf("mysh-0.1$ ");
}


static void parse(char * line, struct cmd_st * res)
{
    char * tok;
    int i = 0;
    while(1)
    {
        tok = strsep(&line,DELIMS);
        if(tok == NULL)
            break;
        if(tok[0] == '\0')
            continue;
        glob(tok, GLOB_NOCHECK | GLOB_APPEND * i, NULL, &res->globres);
        i = 1;
    }
}
int main()
{
    char *linebuf = NULL;
    size_t linebuf_size = 0;
    struct cmd_st res;
    pid_t pid;
    while(1)
    {
        prompt();
        if(getline(&linebuf, &linebuf_size, stdin) < 0 )
        {
            break;
        }

        parse(linebuf, &res);

        if(0)  //internal command)
        {

        }
        else  //external command
        {
            pid = fork();
            if(pid < 0)
            {
                perror("fork():");
                exit(1);
            }
            if(pid == 0)
            {
                //child
                printf("command:%s\n", res.globres.gl_pathv[0]);
                execvp(res.globres.gl_pathv[0], res.globres.gl_pathv);
                exit(1);
            }
            else//parent process
            {
                wait(NULL);
            }
        }
    }
}
