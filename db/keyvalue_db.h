#ifndef _KEYVALUE_DB_H
#define _KEYVALUE_DB_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define static_properties sizeof(int) + sizeof(size_t)

struct database_struct {
    char username[100];
    char password[30];
    int state;
};

struct database_prop {
    int mem_cureent_size;
    size_t database_struct_size;
    struct database_struct *database_struct;
    char *filename;
};

// private func
void db_putsize(FILE *filectx, int sizeofarr);

void database_init(struct database_prop *dbctx, size_t database_struct_size, char *filename);
void database_add(struct database_prop *dbctx, char *username, char* password, int state);
void database_cleanup(struct database_prop *dbctx);
void database_write(struct database_prop *dbctx);


void debug_database_show(struct database_prop *dbctx, int index);
void database_clean(struct database_prop);


#endif