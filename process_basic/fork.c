/***********************************************************************
 
 *Function:main
 *Description:test fork.
 *Input:none
 *Output:none
 *Notice:befor forking, buffer and cache should be flushed
 *       parent process and child process are not in order, which is decided *       by the system, so parent process sleep 1 second to make sure that
 *       child process run first(not absolutrly).
 * ********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    pid_t pid;
    printf("[%d]:Begin!\n", getpid());

    fflush(NULL);  /**very important. stdout uses row buffer mode, file uses all buffer**/
    pid = fork();
    if(pid < 0)
    {
        perror("fork():");
        exit(1);
    }
    if(pid == 0)  //child
    {
        printf("[%d]:Child is working!\n", getpid());
    }
    else          //parent
    {
        sleep(1);
        printf("[%d]:Parent is working!\n", getpid());

    }
    printf("[%d]End!\n", getpid());
    exit(0);
}
