#include <stdio.h>
#include <stdlib.h>

struct who {
    int aaa;
    char bin1s;
};

typedef struct who who_t;

who_t* fn()
{
    struct who *who;
    who = malloc(sizeof(struct who));
    who->aaa = 9;
    who->bin1s = '2';

    return who;
}

int main()
{
    who_t *ss;
    ss = fn();

    printf("%d", ss->aaa);
    free(ss);
}