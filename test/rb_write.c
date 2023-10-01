#include <stdio.h>

struct test1
{
    char buf[100];
    int  bufint;
};
int main()
{
    struct test1 testhm[2] = {
        {"riyanto", 20},
        {"fadhil", 80}
    };

    FILE *fd = fopen("bin.test", "wb");
    fwrite(&testhm, sizeof(testhm), 2, fd);
    return 0;
}