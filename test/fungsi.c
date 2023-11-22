#include <stdio.h>
int f(int x) {

    int a = (2 * x + 6);
    int b = (x - 4);

    int res = a / b;

    return res; 
}


int main()
{
    printf("hasil %d\n", f(5));
}