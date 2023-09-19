#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    char buffer[1024] = "hai wkwk";
    char *bufint = buffer;

    bufint += 4;
    printf("data:  \"%s\"", bufint);

}