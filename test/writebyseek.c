#include <stdio.h>
#include <sys/types.h>

struct test1 // 101 size
{
    char buf[100];  // 100
    u_int8_t somedata; // 1
};

int main()
{
    char bufint = 0;
    FILE *fd = fopen("inttest.test", "wb");

    bufint = 3;
    fwrite(&bufint, sizeof(char), 1, fd);
    fseek(fd, sizeof(char), SEEK_SET);
    bufint = 9;
    fwrite(&bufint, sizeof(char), 1, fd);
    return 0;
}