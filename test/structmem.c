#include <stdio.h>


struct hai {
    int angka;
};

void func1(struct hai *hai)
{
    hai[9].angka = 9;
}

int main()
{
    struct hai hai[10];
    func1(hai);

    printf("dataku %d\n", hai[9].angka);
    
    return 0;
}