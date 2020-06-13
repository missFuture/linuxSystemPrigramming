#include <stdio.h>
#include <stdlib.h>

#define PATH "/tmp/out"

int main(int argc, char ** argv)
{
    FILE *fd = NULL;
    char data[] = "123fasd";
    fd =  fopen(PATH, "w");
    if(fd == NULL)
    {
        perror("fopen():");
        exit(1);
    }

    if(fprintf(fd, "%d\n", atoi(data)) < 0 )
    {
        fprintf(stderr, "fprintf error().\n");
        fclose(fd);
        exit(1);
    }
    fclose(fd);
    exit(0);
}
