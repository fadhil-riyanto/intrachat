#include "keyvalue_db.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int ret;
    FILE *filectx;
    struct database_prop dbctx;
    struct database_struct dbstruct;


    database_init(&dbctx, sizeof(struct database_struct), "binwrite.test");

    debug_database_show(&dbctx, 0);
    debug_database_show(&dbctx, 1);
    debug_database_show(&dbctx, 2);
    debug_database_show(&dbctx, 3);
    

    // file_write(&filectx, &dbctx, sizeof(struct database_struct));
    //database_write(&dbctx);
    database_cleanup(&dbctx);

    
    // file_loads(&filectx, &dbctx);
}