#include <stdio.h>

struct database_struct {
    char *username;
    char *password;
    int state;
};

int main()
{
    FILE *file;
    size_t size;
    struct database_struct *dbctx;
    
    unsigned char buf[1024];

    FILE *fd = fopen("binwrite.test", "rb");
    fread(buf, sizeof(struct database_struct), 3, fd);

    
    dbctx = (struct database_struct*)buf;
    printf("data %s\n", dbctx[0].username);

    return 0;
}