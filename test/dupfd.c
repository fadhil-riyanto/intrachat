#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    char buffer[3];
    char *buftemp;
    int readret;
    int fd = open("hai.txt", O_ASYNC | O_RDONLY);

    printf("file open fd %d\n", fd);

    while(1)
    {
        readret = read(fd, buffer, 3);
        buftemp =  buffer;
        
    }
    


    buffer[readret] = '\0';
    printf("data ret %d %s", readret, buffer);
}