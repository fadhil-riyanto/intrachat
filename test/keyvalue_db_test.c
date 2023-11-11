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

    // database_add(&dbctx, "fadhil riyanto", "123", 0);
    // database_add(&dbctx, "fadhil riyanto", "123", 0);
    // database_add(&dbctx, "wkwk", "fewf", 0);
    // database_add(&dbctx, "fr3ree", "inifree yak", 0);
    // database_add(&dbctx, "testit", "somthig yak", 0);
    // database_add(&dbctx, "testits2", "somethingggs yak", 0);
    // database_add(&dbctx, "hi", "sucks yak", 0);
    // database_add(&dbctx, "newdata", "simple", 0);

    // debug_database_show(&dbctx, 0);
    // debug_database_show(&dbctx, 1);
    // debug_database_show(&dbctx, 2);
    // debug_database_show(&dbctx, 3);
    // debug_database_show(&dbctx, 4);
    // debug_database_show(&dbctx, 5);

    // file_write(&filectx, &dbctx, sizeof(struct database_struct));
    free(dbctx.database_struct);

    
    // file_loads(&filectx, &dbctx);
}