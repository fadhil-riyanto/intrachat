#ifndef _KEYVALUE_DB_H
#define _KEYVALUE_DB_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define static_properties sizeof(int) + sizeof(size_t)

struct database_struct {
    char *username;
    char *password;
    int state;
};

struct database_prop {
    int mem_cureent_size;
    size_t database_struct_size;
    struct database_struct *database_struct;
};

void database_init(struct database_prop *dbctx, size_t database_struct_size);
void database_add(struct database_prop *dbctx, char *username, char* password, int state);

void debug_database_show(struct database_prop *dbctx, int index);
void database_clean(struct database_prop);

// file operations
int file_open(FILE **filectx, char *filename, const char *mode);
int file_loads(FILE **filectx, struct database_prop *dbctx);

#endif