#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

static int prepare_sockfd(int *udpfd_ptr, char *addr, int port, int is_nonblock)
{
    int sock_type, err, ret;

    struct sockaddr_in sockaddr_in;

    if (is_nonblock == 1) {
        sock_type = SOCK_DGRAM | SOCK_NONBLOCK;
    } else {
        sock_type = SOCK_DGRAM;
    }

    *udpfd_ptr = socket(AF_INET, sock_type, 0);
    printf("%d\n", *udpfd_ptr);
    if (*udpfd_ptr == -1) {
        err = errno;
        perror("socket() error");
        return err;
    }
    
    memset(&sockaddr_in, 0, sizeof(sockaddr_in));

    sockaddr_in.sin_family = AF_INET;
    sockaddr_in.sin_port = htons(port);
    sockaddr_in.sin_addr.s_addr = inet_addr(addr);
    
    ret = bind(*udpfd_ptr, (const struct sockaddr*) &sockaddr_in, sizeof(sockaddr_in));
    if (ret == -1) {
        err = errno;
        perror("bind() error");
        close(*udpfd_ptr);
        return err;
    }
    return 0;

}

int main()
{
    int udpfd;
    char *addr = "127.0.0.1";
    int port = 8888;
    int is_nonblock = 0;
    struct sockaddr_in clientaddr;
    socklen_t slen = sizeof(clientaddr);

    char buf[1024];
    prepare_sockfd(&udpfd, addr, port, is_nonblock);

    for(;;)
    {
        memset(buf, 0, sizeof(buf));
        recvfrom(udpfd, buf, sizeof(buf), 0, (struct sockaddr *)&clientaddr, &slen);

        printf("received: \"%s\"\n", buf);

        printf("addr: \"%s\"\n", inet_ntoa(clientaddr.sin_addr));
        char* msg = "apa wkek";

        sendto(udpfd, msg, strlen(msg), 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    }

}

