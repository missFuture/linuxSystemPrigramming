#include <stdio.h>
#include <stdlib.h>

int main()
{
    fprintf(stdout, "OK");
    fflush(NULL);
    while(1);
    fprintf(stdout, "OK\n");

    exit(0);
}
