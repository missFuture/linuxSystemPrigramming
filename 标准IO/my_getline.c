/*************************************************************************
 *Function: my_getline
 *Description: This file is implementaion of getline
 *Input: lineptr, is used to save current line result
 *       n, current malloc space to save line result(more than current line  *       length)
 *       fp, file stream to read
 *Output: current line length
 *
 *Function: main
 *Description: test my_getline
 *Input: file name to read
 *output: each line result, line length and malloc space lenth
 *Example: ./my_getline hello
 *
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
ssize_t  my_getline(char ** lineptr, size_t *n, FILE *fp)
{

    char* buffer;
    ssize_t i = 0; // string length
    char c;
    if(buffer == NULL || *n == 0)
    {
        buffer = malloc(10);
        *n = 10;
        (*lineptr) = buffer; 
    }
    while((c = fgetc(fp)) != '\n')
    {
        if(c == EOF)
        {
            return -1;
        }
        if(i < (*n - 2))
        {
            *(buffer + i++) = c;
        }
        else
        {
            *n = *n  + 10;
            buffer = realloc(buffer, *n);
            (*lineptr) = buffer;
            *(buffer + i++) = c;
        }
    }
    *(buffer + i++) = '\n';
    *(buffer + i ) = '\0';
    return i;   
}

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Usage: %s filename", argv[0]);
        exit(1);
    }
    FILE *fp = fopen(argv[1], "r");
    if(!fp)
    {
        fprintf(stderr, "fopen():\n");
        exit(1);
    }
    char *buf = NULL;
    size_t i = 0;
    ssize_t l;
    while((l = my_getline(&buf, &i, fp)) != EOF)
    {
        printf("str:%s, len:%zu, i:%zd\n", buf, l, i);
        free(buf);
        i = 0;
    }
    free(buf);
    fclose(fp);
    exit(0);
}
