#include <unistd.h>
#include <stdio.h>

int file_exist(char* file_name)
{
    if (access(file_name, F_OK) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int file_create_if_not_exist(char *filename)
{
    FILE *fd = fopen(filename, "ab+");
    return 0;
}


int main()
{
    printf("%s", (file_create_if_not_exist((char*)"createtest1.test") == 1 ? "true" : "false"));
}