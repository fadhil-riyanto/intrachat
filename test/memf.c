#include <stdio.h>
#include <string.h>


void myfn(void *ptr)
{
    printf("hi fn");
}

int runner(void *(*routine)(void*)) {
    routine(NULL);
    return 0;
}

int main()
{
    char *data;

    //data = "aaaa";

    printf("%s\n", (*data == 0) ? "true" : "false");
    //runner((void*)myfn);
}

