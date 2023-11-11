#include <stdio.h>
#include <sys/types.h>

struct test1 // 101 size
{
    char buf[100];  // 100
    u_int8_t somedata; // 1
};

int main()
{
    char buf;
    FILE *fd = fopen("inttest.test", "rb");
    fread(&buf, sizeof(char), 1, fd);
    fseek(fd, sizeof(char), SEEK_SET);
    fread(&buf, sizeof(char), 1, fd);

    printf("%d", buf);
    

    // struct test1 testhm[5] = {
    //     {"riyanto", 9},
    //     {"fadhil", 8},
    //     {"fox", 8},
    //     {"wkwk", 100},
    //     {"loss", 99}
    // }; // sum 101 * 3
    

    
    // fseek(fd, 0, SEEK_END); 
    // fwrite(&testhm, sizeof(testhm), 5, fd);

    // printf("size struct %lu\n", sizeof(struct test1) * 3); // sizeof mod by 2
    return 0;
}