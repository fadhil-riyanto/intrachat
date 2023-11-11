#include <stdio.h>
#include <sys/types.h>

struct test1 {
    char *username;
    char *password;
    int state;
};

int main()
{
    struct test1 testhm[5] = {
        {"riyanto", "wkwk", 1},
        {"fadhil", "wkwk", 1},
        {"fox", "wkwk", 1},
        {"wkwk", "wkwk", 1},
        {"loss", "something", 1}
    }; // sum 101 * 3

    FILE *fd = fopen("binwrite.test", "wb");
    fwrite(&testhm, sizeof(testhm), 5, fd);

    printf("size struct %lu\n", sizeof(struct test1) * 3); // sizeof mod by 2
    return 0;
}