#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "keyvalue_db.h"

void database_init(struct database_prop *dbctx, size_t database_struct_size)
{ 
    dbctx->mem_cureent_size = 1;
    dbctx->database_struct_size = database_struct_size;
    dbctx->database_struct = malloc(database_struct_size * dbctx->mem_cureent_size);
}

void database_add(struct database_prop *dbctx, char *username, char* password, int state)
{
    dbctx->mem_cureent_size = dbctx->mem_cureent_size + 1;
    dbctx->database_struct = realloc(dbctx->database_struct, dbctx->database_struct_size * dbctx->mem_cureent_size);

    dbctx->database_struct[dbctx->mem_cureent_size - 2].username = username;
    dbctx->database_struct[dbctx->mem_cureent_size - 2].password = password;
    dbctx->database_struct[dbctx->mem_cureent_size - 2].state = state;

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
    
}