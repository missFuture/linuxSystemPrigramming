#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    int cnt = 0;
    FILE *fd = NULL;
    if(argc < 2)
    {
        fprintf(stderr, "Usage: .//%s filename\n", argv[0]);
        exit(1);
    }
    fd =  fopen(argv[1], "r");
    if(fd == NULL)
    {
        perror("fopen():");
        exit(1);
    }
    while(fgetc(fd) != EOF)
    {
        cnt++;
    }
    fprintf(stdout, "total %d bytes.\n", cnt);
    fclose(fd);
    exit(0);
}
