/***********************************************************************
 *Function:main
 *Description:compute primer number between LEFT and WRIGHT.
 *Input:none
 *Output:none
 *Notice:use PROCEENO processes to compute primer number in cross distributi *       on way.for example 0,3,6,9...belong to first process, 1,4,7,10..bel *       ong to second process,2,5,8,11..belong to the third process
 *
 **********************************************************************/ 
#include <stdio.h>
#include <stdlib.h>
#define LEFT 20000
#define RIGHT 20200
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#define PROCESSNO 3
int main()
{

    int mark = 0;
    pid_t pid = 0;
    for(int n = 0; n < PROCESSNO; n++)
    {
     fflush(NULL);
     pid = fork();
     if(pid < 0)
     {
        perror("fork():");
        exit(1);
     }
     if( pid == 0)
     {
        for(int i = LEFT + n; i <= RIGHT; i+= PROCESSNO)
        {
            mark = 1;
            for(int j = 2; j <= (i / 2); j++)
            {
               if(i % j == 0)
               {
                  mark = 0;
                  break;
               }
            }
            if(mark == 1)
            {
                printf("[%d:] %d is a primer.\n", getpid(), i);
            }
        }
        exit(0);   
     }
    }
    for(int i = 0; i < PROCESSNO; i++)
    {
        wait(NULL);
    }
    exit(0);
}
