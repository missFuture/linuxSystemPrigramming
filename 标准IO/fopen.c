#include <stdio.h>
#include <stdlib.h>
#define PATH "/tmp/out"
int main()
{
    FILE *fd = NULL;
    char data[] = "OK\n";

    fd = fopen(PATH, "w");
    if(fd == NULL)
    {
        perror("fopen():");
        exit(1);
    }
    if(fputs(data,fd) < 0)
    {
        fprintf(stderr, "fputs error.\n");
        fclose(fd);
        exit(1);
    }
    fclose(fd);
    exit(0);
}
