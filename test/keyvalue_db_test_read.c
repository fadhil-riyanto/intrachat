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
    //file_loads(&filectx, &dbctx);

    debug_database_show(&dbctx, 0);
    debug_database_show(&dbctx, 1);
    debug_database_show(&dbctx, 2);
    debug_database_show(&dbctx, 3);
    debug_database_show(&dbctx, 4);
    debug_database_show(&dbctx, 5);
    debug_database_show(&dbctx, 6);
    debug_database_show(&dbctx, 7);


    // debug_database_show(&dbctx, 2);
    // debug_database_show(&dbctx, 1);
    database_cleanup(&dbctx);


    
    // file_loads(&filectx, &dbctx);
}