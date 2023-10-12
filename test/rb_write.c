#include <stdio.h>
#include <sys/types.h>

struct test1 // 101 size
{
    char buf[100];  // 100
    u_int8_t somedata; // 1
};

int main()
{
    struct test1 testhm[5] = {
        {"riyanto", 9},
        {"fadhil", 8},
        {"fox", 8},
        {"wkwk", 100},
        {"loss", 99}
    }; // sum 101 * 3

    FILE *fd = fopen("bin1.test", "wb");
    fwrite(&testhm, sizeof(testhm), 5, fd);

    printf("size struct %lu\n", sizeof(struct test1) * 3); // sizeof mod by 2
    return 0;
}