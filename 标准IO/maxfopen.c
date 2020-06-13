#include <stdio.h>
#include <stdlib.h>
/*
this program is to validate the max number of filse that one process can open, the result is 1021, the default file stream are stdin stdout, stderr
*/

int main()
{
    int cnt = 0;
    FILE *fd = NULL;
    while(1)
    {
        fd = fopen("tmp", "w");
        if(fd == NULL)
        {
            printf("max open file number : %d\n", cnt);
            perror("fopen()");
            exit(1);
        }
        cnt ++;

    }
    exit(0);
}
