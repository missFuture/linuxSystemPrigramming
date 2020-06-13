#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 1024
int main(int argc, char ** argv)
{
    FILE* fd1 = NULL;
    FILE* fd2 = NULL;
    char buffer[BUFFERSIZE];
    if(argc < 3)
    {
        fprintf(stderr, " Usage : %s <source file name> <destination file name>.\n", argv[0]);
        exit(1);
    }

    fd1 = fopen(argv[1], "r");
    if(fd1 == NULL)
    {
        fprintf(stderr, "fopen():\n");
        exit(1);
    }

    fd2 = fopen(argv[2], "w");
    if(fd2 == NULL)
    {
        fprintf(stderr, "fopen():\n");
        fclose(fd1);
        exit(1);
    }

    while(fgets(buffer, BUFFERSIZE, fd1) != NULL)
    {
        if(fputs(buffer, fd2) < 0 )
        {
            fprintf(stderr, "fputs error\n");
            fclose(fd1);
            fclose(fd2);
            exit(1);
        }

    }

    fclose(fd1);
    fclose(fd2);
    exit(0);
}

