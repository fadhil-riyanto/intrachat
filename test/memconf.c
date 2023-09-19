#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int *data = (int*)malloc(sizeof(int) * 1000000000);

    for ( int a = 0; a < 1000000000; a++)
    {
        data[a] = 10000;
    }

    printf("dataku \"%d\"", data[0]);
    sleep(3);
    free(data);
}