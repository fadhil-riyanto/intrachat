
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DEBUG 1

void dprintln(char* fmt, ...)
{

    va_list arglist_ptr;
    va_start(arglist_ptr, fmt);

    vprintf(fmt, arglist_ptr);
    va_end(arglist_ptr);

    
}

int main()
{
    dprintln("%d and %d", 2, 33,22);
}