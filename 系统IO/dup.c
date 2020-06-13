/***********************************************************************
 *Funtion main
 *Requirement: please do not change the code after / **** /, output the stri *             ng to "/tmp/out"
 *Description: test dup program, dup is used to copy a file free descriptor  *              to the parameter fp, before that, No.1 file descriptor is cl *             osed, dup(fp) set fp = 1 normally. Under parallel condition,  *             No.1 file descriptor may be used by other process(or thread)  *             it is not atomic. dup2 can solve this problem
 *Input: none
 *Output:write "hello world" to /tmp/out
 *
 *
 * *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#define FILENAME "/tmp/out"
int main()
{
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if(fd < 0)
    {
        perror("open()");
        exit(1);
    }
   close(1);
   dup(fd);

/*********************/
    puts("hello world!");
    exit(0);
}
