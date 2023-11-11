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
    FILE *fd = fopen("inttest.test", "rb");
    fread(&bufint, sizeof(char), 1, fd);
    printf("%d\n", bufint);

    fseek(fd, sizeof(char), SEEK_SET);
    fread(&bufint, sizeof(char), 1, fd);
    printf("%d\n", bufint);

    return 0;
}