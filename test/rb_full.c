#include <asm-generic/errno-base.h>
#include <stddef.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

struct test;

size_t db_fguess_size(FILE* fd)
{
    size_t ret;
    fseek(fd, 0, SEEK_END);
    ret = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    return ret;
}

long db_fguess_arrsize(size_t file_size, size_t structsize)
{
    long ret;
    ret = file_size / structsize;
    return ret;
}

// read func
int db_read(FILE* filectx)
{
    printf("%p\n", filectx);
    return 0;
}

struct test {
    char *username;
    char *password;
    int state;
};

int main()
{
    long size;
    unsigned char *buf;
    struct test *test;

    FILE *filectx;
    filectx = fopen("binwrite.test", "rb");
    printf("%p\n", filectx);

    printf("trying allocate %lu\n", db_fguess_size(filectx));

    int realsize = db_fguess_size(filectx) / 2;
    u_int8_t arrsize = db_fguess_arrsize(realsize, sizeof(struct test));

    buf = malloc(5 * sizeof(struct test));
    if (!buf) {
        return ENOMEM;
    }
    
    fread(buf, realsize, arrsize, filectx);

    test = (struct test*)buf;
    int i = 0;
    for(;;) {
        printf("index %d | %s, %s\n", i, (char*)test[i].username, (char*)test[i].password);
        if (i < (arrsize - 1) ) { 
            i++;
        } else {
            break;
        }
        
    }
    printf("end at %d\n", i);
    free(buf);
    fclose(filectx);

}