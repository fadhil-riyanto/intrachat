#include "keyvalue_db.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int ret;
    // struct database_prop dbctx;
    // struct database_struct dbstruct;

    // database_init(&dbctx, sizeof(struct database_struct));

    // database_add(&dbctx, "fadhil", "123", 0);
    // database_add(&dbctx, "slav", "222", 0);
    // database_add(&dbctx, "atarashii", "8888", 0);

    // debug_database_show(&dbctx, 0);
    // debug_database_show(&dbctx, 2);
    // debug_database_show(&dbctx, 1);

    // free(dbctx.database_struct);

    FILE *filectx;
    ret = file_loads(&filectx,"hai.txt", "r");
    if(ret != 0) {
        return 1;
    }

    

    fclose(filectx);
}