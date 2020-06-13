/*****************************************************
 *Function:my_atoi
 *Description:implementaion of atoi
 *Input:string need to convert
 *Output:result of converting
 *
 *Function:main
 *Description:test my_atoi
 *Input:a string
 *Ouput:result of converting
 *
 *Example: ./my_atoi 1234    result 1234
 *          ./my_atoi 124df   result 124
 *****************************************************/
#include <stdio.h>
#include <stdlib.h>

int my_atoi(const char* str)
{
    int res = 0;
    int i = 0;
    while(str[i] != EOF)
    {
        if(str[i] <= '9' && str[i] >= '0')
        {
            res = res * 10 + str[i] - '0';
            i++;
            continue;
        }
        break;
    }
    return res;
}

int main(int argc, char * argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage:%s string\n", argv[0]);
        exit(1);
    }
    printf("%d\n", my_atoi(argv[1]));
    exit(0);
}
