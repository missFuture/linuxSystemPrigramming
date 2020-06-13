/***********************************************************************
 *Function:main
 *Description:compute primer number between LEFT and RIGHT
 *Input:none
 *Output:primer number between LEFT and RIGHT
 *Notice:(RIGHT-LEFT) processes are used. In fact, there may not be so many  *        preocess to fork
 *
 * ********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define LEFT 20000
#define RIGHT 20200
#include <sys/types.h>
#include <unistd.h>
int main()
{

    int mark = 0 ;
    pid_t pid = 0;
    for(int i = LEFT; i <= RIGHT; i++)
    {

        fflush(NULL);
        pid = fork();
        if(pid < 0)
        {
            perror("fork():");
            exit(1);
        }
        if(pid == 0)  //child process
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
            exit(0);//child exit normally
        }

    }
    exit(0);
}
