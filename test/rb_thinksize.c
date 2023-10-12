#include <stdio.h>
#include <sys/types.h>

struct test1 // 101 size
{
    char buf[100];  // 100
    u_int8_t somedata; // 1
};

int main()
{
    FILE *file;
    size_t size;
    char *buf;

    FILE *fd = fopen("bin1.test", "rb");

    fseek(fd, 0, SEEK_END); 
    size = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    

    printf("sizeof() is %zu\n", size);
    printf("arr val is %lu\n", (size / 2) / sizeof(struct test1));

    // fread(&buf, sizeof(buf), (sizeof(buf) / sizeof(buf[0])), fd);

    //struct test1 *test1 = (struct test1*)buf;
    return 0;
}