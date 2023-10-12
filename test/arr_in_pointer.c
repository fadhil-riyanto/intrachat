#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct database_struct {
    char username[60];
    char password[8];
    int state;
};

struct complicated {
    int nums;
    struct database_struct *database;
};

int main()
{
    struct complicated *dbs;
    dbs = malloc(sizeof(struct complicated));

    struct database_struct ke0 = {"woi", "wkwk", 0};
    dbs->database[0] = ke0;

    struct database_struct ke1 = {"dddd", "wewef", 0};
    dbs->database[1] = ke1;

    //printf("%s\n data ke 0", dbs->database[0].username);
}