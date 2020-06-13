/***********************************************************************
 *Function:main
 *Description:copy file1 to file2 by stdio
 *Usage:./copySys source_filename destination_filename
 *Input:source filename file1
 *      destination filename file2
 *Output:none
 *
 **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFERSIZE 1024
int main(int argc, char ** argv)
{
    int sfd;//source file descriptor
    int dfd;//destination file descriptor
    char buf[BUFFERSIZE];//read buffer
    int read_return = 0;
    int write_return = 0;
    int pos = 0;
    if(argc < 3)
    {
        fprintf(stderr, "Usage:...\n");
        exit(1);
    }
    sfd = open(argv[1], O_RDONLY);//only read
    if(sfd < 0)
    {
        perror("open():");
        exit(1);
    }

    dfd = open(argv[2],O_WRONLY | O_TRUNC | O_CREAT,0600);
    if(dfd < 0 )
    {
        close(sfd);//close last fd
        perror("open()");
        exit(1);
    }
    while(1)
    {
        read_return = read(sfd, buf, BUFFERSIZE);
        if(read_return < 0 )
        {
            perror("read error.");
            break;//need to run close
        }
        if(read_return == 0)
           break;
        while(read_return > 0 )
        {
            write_return = write(dfd, buf+pos, read_return);

            if(write_return < 0)
            {
                perror("write error");
                exit(1);
            }
            pos += write_return;
            read_return -= write_return;
        }
    }
    close(sfd);
    close(dfd);
    exit(0);
}
