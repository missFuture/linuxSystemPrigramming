/**********************************************************************
 *Function:main
 *Description:compute primer number between LEFT and RIGHT
 *Input:none
 *Output:primer number between LEFT and RIGHT
 *Nodtice:one process is used under this program.
 *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define LEFT 20000
#define RIGHT 20200

int main()
{

    int mark = 0 ;
    for(int i = LEFT; i <= RIGHT; i++)
    {
        mark = 1;
        for(int j = 2; j <= (i / 2); j++)
        {
            if(i % j == 0)
            {
                mark = 0;
                break;
            }
        }
        if(mark == 1)
        {
            printf("%d is a primer.\n", i);
        }
    }
    exit(0);
}
