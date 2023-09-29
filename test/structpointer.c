#include <stdio.h>
#include <string.h>

struct data {
    char buf[10];
};

void test1(struct data *data)
{
    printf("data %s", data[1].buf);
}
int main()
{
    struct data data[5];

    strcpy(data[1].buf, "woilah");
    test1(data);

    return 0;
}