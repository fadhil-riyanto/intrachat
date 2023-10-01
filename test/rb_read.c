#include <stdio.h>

struct test1
{
    char buf[100];
    int  bufint;
};
int main()
{
    FILE *file;
    size_t size;
    unsigned char buf[1024];
    struct test1 test[2];

    FILE *fd = fopen("bin.test", "rb");
    fread(&test, sizeof(struct test1), 2, fd);

    printf("data %s\n", test[0].buf);

    return 0;
}