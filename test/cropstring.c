#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void cropstr(char **source, long length)
{
    char *buf;
    buf = malloc(sizeof(char) * (length + 1));
    strcpy(buf, *(&source));
    // buf[length -1 ] = '\0';
    // printf("%s\n", buf);

    // //strcpy(source, buf);
    // *source = *buf;
    //free(buf);
}

int main()
{
    char *abc = "asjsk";
    cropstr(abc, strlen(abc));
    printf("%s\n", abc);
}