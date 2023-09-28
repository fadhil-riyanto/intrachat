#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#define LOGGER 1


void concat(char **res, char *str1, char* str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int max = len1 + len2 + 1;
    char buf[max];
    int i = 0;

    for(;i < len1; i++) {
        buf[i] = str1[i];
    }

    for(int a = i; a < max - 1; a++) {
        buf[a] = str2[ (a - len1)];
    }

    buf[max - 1] = '\0';
    *res = buf; 
}
void logptest(char *event_name, char* fmt, ...)
{
    if (!LOGGER) {
        return;
    }

    char buf0[1024];
    char buf1[1024];
    char *buf2;

    sprintf(buf0, "[ %s ] : ", event_name);

    va_list arglist_ptr;
    va_start(arglist_ptr, fmt);

    sprintf(buf1, fmt, arglist_ptr);

    va_end(arglist_ptr);
    concat(&buf2, buf0, buf1);
    printf("%s\n", buf2);
    
}

int main()
{
    char *data;
    concat(&data, "hi ", "bro");

    printf("%s\n", data);
}