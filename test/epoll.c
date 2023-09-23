#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>

int main()
{
    int epoll_fd;
    epoll_fd = epoll_create1(0);

    if (epoll_fd == -1)
    {
        close(epoll_fd);
        perror("epoll err");
    }
    printf("epfd %d\n", epoll_fd);
    fprintf(stdout, "epoll succes");

    close(epoll_fd);
    return 0;

}