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

void logp()

/*
 * testing 
 * cek termination karakter di char *
 * cek keberadaan termination di char [100]
 */
void tes0()
{
    // in position
    char *data = "hai"; 
    printf("%s\n", ((data[3]) == '\0') ? "true" : "false");

    char data1[100] = "ojk"; 
    printf("%s\n", ((data1[3]) == '\0') ? "true" : "false");

    // before position
    printf("%s\n", ((data[2]) == '\0') ? "true" : "false");

    printf("%s\n", ((data1[2]) == '\0') ? "true" : "false");

    // after position
    printf("%s\n", ((data[4]) == '\0') ? "true" : "false");

    printf("%s\n", ((data1[4]) == '\0') ? "true" : "false");

    // overloaded
    printf("%s\n", ((data1[99]) == '\0') ? "true" : "false");

    // conlusion, the map of string memory
    /*
     * using char*, the memaddr look like this 
     * ... | h | a | i |\0| ....
     *       ^~ pointer start here
     * 
     * meanwhile using char[100]
     * ... | o | j | k |\0|\0|\0| ... until 100
     *       ^~~~~~~~~~~~~~~~~~~~ accesed by indexing, \
     *                            useng & as pointer
     */
}

/*
 * knowing if the 0 in char is same as null, and 0 same as \n
 */

void tes1()
{
    // test using char
    char data[100] = "";
    printf("%s\n", ((data[0]) == 0) ? "true" : "false");
    printf("%s\n", ((data[0]) == '\0') ? "true" : "false");

    // compare if \0 same as 0
    printf("%s\n", (0 == '\0') ? "true" : "false");
}

/*
 * reset a string
 */
void tes2()
{
    char data[100] = "hai";

    // make sure all data is valid
    printf("%s\n", ((data[0]) == 'h') ? "true" : "false");

    memset(&data, 0, sizeof(data));
    printf("%s\n", ((data[0]) == 'h') ? "true" : "false");

    // check address
    printf("the 1st index address %p\n", &data[0]);
    printf("the array address %p\n", &data);

}

void tes3()
{
    char data[100] = "hai";

    
    printf("the array address %lu\n", strlen(&data[0]));

}

int main()
{
    char *data;
    // concat(&data, "hjkl ", "la");

    // printf("%s\n", data);
    logp("epoll", "%s event occured", "cleaning thread");
}