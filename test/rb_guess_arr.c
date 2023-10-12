#include <stdio.h>

struct test1
{
    char buf[100];
    int  bufint;
};
int main()
{
    size_t size;
    struct test1 *test = ;

    FILE *fd = fopen("bin.test", "rb");
    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    printf("sizeof is %lu", (size / sizeof(struct test1)));

    // fread(&test, sizeof(struct test1), 2, fd);

    // printf("data %s\n", test[0].buf);

    return 0;
}