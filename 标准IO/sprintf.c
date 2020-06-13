#include <stdio.h>
#include <stdlib.h>
#define DATASIZE 20
int main()
{
    char data[DATASIZE];
    int year = 2020;
    int month = 6;
    int day = 7;
    sprintf(data, "%d-%d-%d", year, month, day);
    puts(data);
    exit(0);
}
