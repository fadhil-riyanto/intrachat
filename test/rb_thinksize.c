#include <stdio.h>

struct test1
{
    char *buf;
    int  bufint;
};
int main()
{
    FILE *file;
    size_t size;
    char *buf;

    FILE *fd = fopen("variadic.c", "rb");

    fseek(fd, 0, SEEK_END); 
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    printf("sizeof() variadic.c is %zu\n", size);

    // fread(&buf, sizeof(buf), (sizeof(buf) / sizeof(buf[0])), fd);

    //struct test1 *test1 = (struct test1*)buf;

    printf("data num 1 %s", buf);
    return 0;
}