#include "keyvalue_db.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int ret;
    struct database_prop dbctx;
    struct database_struct dbstruct;

    database_init(&dbctx, sizeof(struct database_struct), 
        "binwrite.test");


    // database_add(&dbctx, "test0", "123", 0);
    // database_add(&dbctx, "test1", "222", 1);
    // database_add(&dbctx, "test2","323", 1);

    // database_write(&dbctx);
    // database_cleanup(&dbctx);
}