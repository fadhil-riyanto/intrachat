#include "utils.h"
#include "config.c"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void dprint(char* fmt, ...)
{
    if (!DEBUG) {
        return;
    }
    va_list arglist_ptr;
    va_start(arglist_ptr, fmt);

    vprintf(fmt, arglist_ptr);
    va_end(arglist_ptr);
    
}

void logp(char* fmt, ...)
{
    if (!LOGGER) {
        return;
    }
    va_list arglist_ptr;
    va_start(arglist_ptr, fmt);

    vprintf(fmt, arglist_ptr);
    va_end(arglist_ptr);
    
}