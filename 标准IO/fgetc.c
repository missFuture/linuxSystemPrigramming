#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* sfd = fopen("hello", "r");
    if(sfd < 0 )
    {
        perror("fopen()");
        exit(1);
    }
    char c;
    while((c = fgetc(sfd)) != '\n')
    {
        printf("%c\t", c);
    }
    printf("\n");
    fclose(sfd);
    exit(0);
}
