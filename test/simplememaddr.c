#include <unistd.h>
int main()
{
    asm volatile (  ".text" 
                    "c: .long 0x04D2"
                    "");
}