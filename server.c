#include "server.h"
#include <bits/pthreadtypes.h>
#include <errno.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>

int volatile emergency_exit = 0;

void signal_handler(int signal_recv_number)
{
    printf("we've got %d signal, exiting\n", signal_recv_number);
    emergency_exit = 1;
}

void do_eventloop(int *udp_fd, pthread_t *handle_conn_thread)
{
    while(1){
        if (emergency_exit == 1) {
            close(*udp_fd);
            pthread_cancel(*handle_conn_thread);
            printf("exit succesfully\n");
            break;
        }
    }
}

void *handle_incoming_conn(void *ptr)
{
    int *udp_fd = (int*)ptr;
    char buf[4096];
    struct sockaddr_in clientAddress;

    socklen_t socklen = sizeof(clientAddress);
    while (1)
    {
        memset(&buf, 0, sizeof(buf));
        recvfrom(*udp_fd, &buf, sizeof(buf), 0, (struct sockaddr *)&clientAddress, (socklen_t *)sizeof(clientAddress));
        printf("udp recvbuf: %s", buf);

        
    }
}

int create_udp_server() 
{
    signal(SIGINT, signal_handler);

    
    struct sockaddr_in sockaddr_in;
    int udp_fd, err, ret;

    pthread_t handle_conn_thread;

    
    udp_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_fd == -1) {
        err = errno;
        perror("socket udp err fd");
        return err;
    }

    // printf("ret %d\n", errno);


    memset(&sockaddr_in, 0, sizeof(sockaddr_in));

    sockaddr_in.sin_family = AF_INET;
    sockaddr_in.sin_port = htons(7000);
    sockaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    
    ret = bind(udp_fd, (const struct sockaddr*) &sockaddr_in, sizeof(sockaddr_in));
    printf("ret %d\n", errno);
    
    pthread_create(&handle_conn_thread, NULL, handle_incoming_conn, (void*)&udp_fd);


   

    do_eventloop(&udp_fd, &handle_conn_thread);
    return 0;

}