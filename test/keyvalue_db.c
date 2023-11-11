#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "keyvalue_db.h"

struct TLV_HEADER
{
    int length;
};

void database_init(struct database_prop *dbctx, size_t database_struct_size, char *filename)
{ 
    FILE *openfd;
    int file_arr_size;
    unsigned char *buf;
    
    
    // // open and make if not exist
    openfd = fopen(filename, "ab+");

    // read first byte
    fread(&file_arr_size, sizeof(int), 1, openfd);

    dbctx->mem_cureent_size = file_arr_size + 1;
    dbctx->database_struct_size = database_struct_size;
    dbctx->database_struct = malloc(database_struct_size * dbctx->mem_cureent_size);

    // // read all
    buf = malloc(sizeof(struct database_struct) * dbctx->mem_cureent_size);
    fread(buf, database_struct_size, file_arr_size, openfd);

    memcpy(dbctx->database_struct, buf, database_struct_size * file_arr_size);
    free(buf);
    fclose(openfd);
    
}

void database_add(struct database_prop *dbctx, char *username, char* password, int state)
{
    dbctx->mem_cureent_size = dbctx->mem_cureent_size + 1;
    dbctx->database_struct = realloc(dbctx->database_struct, dbctx->database_struct_size * dbctx->mem_cureent_size);

    strcpy(dbctx->database_struct[dbctx->mem_cureent_size - 2].username, username);
    strcpy(dbctx->database_struct[dbctx->mem_cureent_size - 2].password, password);
    dbctx->database_struct[dbctx->mem_cureent_size - 2].state = state;

}

void database_cleanup(struct database_prop *dbctx)
{
    free(dbctx->database_struct);
}

void database_write(struct database_prop *dbctx)
{
    FILE *
    int arrsize = dbctx->mem_cureent_size - 1;
    db_putsize(filectx, &dbctx->mem_cureent_size);
    printf("%d\n", dbctx->mem_cureent_size);
    return fwrite(dbctx->database_struct, sizeof(struct database_struct), dbctx->mem_cureent_size, *filectx);
}

void debug_database_show(struct database_prop *dbctx, int index)
{
    printf("username %s\n", dbctx->database_struct[index].username);
    printf("pass %s\n", dbctx->database_struct[index].password);
    //  %s\n", dbctx->database_struct[index].username);
}

int file_open(FILE **filectx, char *filename, const char *mode)
{
    (*filectx) = fopen(filename, mode);
    if ((*filectx) == NULL) {
        perror("open err");
        return EBADFD;
    }

    return 0;
}

int file_loads(FILE **filectx, struct database_prop *dbctx)
{
    int initial_size;
    fread(&initial_size, sizeof(int), 1, *filectx);
    printf("%d size is\n", initial_size);

    // unsigned char *buf = malloc(sizeof(struct database_struct) * initial_size);
    // if (buf == NULL) {
    //     perror("err on memalloc");
    // }
    // fread(buf, sizeof(struct database_struct), initial_size, *filectx);

    
    // get_initial_size = 7;t
    unsigned char *change_initial_size = realloc(dbctx->database_struct, sizeof(struct database_struct) * initial_size);
    //return 0;
    if (!change_initial_size) {
        perror("trying realloc");
    }
    fread(dbctx->database_struct, sizeof(struct database_struct), initial_size, *filectx);

    // dbctx->database_struct = (struct database_struct*)change_initial_size;
    // dbctx->database_struct = (struct database_struct*)buf;
    // free(buf);
    return 0;
}

void db_putsize(FILE **filectx, int *sizeofarr)
{
    int ret;
    size_t sizeofint_sample = sizeof(int);
    int diff_int = (*sizeofarr - 1);

    // sizeof arr -1 because there the initial value is 1, so instead using 0 that cant to be multiplied and the result is 0 memsize
    fwrite(&diff_int, sizeof(int), 1, *filectx);
    
    printf("%lu current stream position\n", ftell(*filectx));

    // set the seek to the upwards pointed by current offset (which is zero) 
    // and add it by size of 1 int multiplied by 2
    //ret = fseek(*filectx, sizeofint_sample, SEEK_SET);
    printf("%d current seek on file\n", ret);
    
    printf("%lu intsize\n", sizeofint_sample);
}

