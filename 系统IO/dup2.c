/***********************************************************************
 *Function:main
 *Description:this program is used to solve the problem in dup.c, dup2 is at *                 omic
 *Input:node
 *Output:write the sting "hello world!" to /tmp/out
 *
 **********************************************************************/
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
   dup2(fd, 1);
   if(fd != 1)
       close(fd);


/*********************/
    puts("hello world!");
    exit(0);
}
