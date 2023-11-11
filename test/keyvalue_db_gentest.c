#include <stdio.h>
#include <sys/types.h>

struct database_struct {
    char *username;
    char *password;
    int state;
    u_int64_t int64;
};

int main()
{
    struct database_struct testdb[4] = {
        {"riyant22222222222222222222222oriyant22222222222222222222222oriyant22222222222222222222222oriyant22222222222222222222222oriyant22222222222222222222222oriyant22222222222222222222222oriyant22222222222222222222222oriyant22222222222222222222222oriyant22222222222222222222222oriyant22222222222222222222222oriyant22222222222222222222222o", "wkwk", 0, 199292},
        {"fadhil", "fehb", 0, 199292},
        {"fox", "wefhwejfk", 0, 199292},
        {"riyanto", "wkwk", 0, 199292}
    }; // sum 101 * 3

    FILE *fd = fopen("bin.test", "wb");
    fwrite(&testdb, sizeof(testdb), 4, fd);

    printf("arr size is %zu\n", sizeof(testdb));
    printf("single struct size %zu\n", sizeof(struct database_struct));
    return 0;
}