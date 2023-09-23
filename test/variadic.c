
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DEBUG 1

struct literate_state
{
    int is_format;

};

void ourln(char* fmt, ...)
{
    char c;
    struct literate_state state;

nextliterate:
    c = *fmt++;

    switch (c) {
        case 'a' ... 'z':
            write(1, c, 1);

        break;

        case '%':
            state.is_format = 1;
            goto nextliterate;
        break;

        case 'd' || state.is_format:
            
        break;



    }

    printf("data %c", c);

    
}

int main()
{
    ourln("dataku %d and %d", 2, 33,22);
}