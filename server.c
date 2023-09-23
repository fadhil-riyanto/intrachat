#include "config.c"
#include "server.h"
#include "utils.h"

#include <bits/pthreadtypes.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

void pthread_stack_state_reset(struct event_stack *event_stack)
{
    for(int i = 0; i < MAX_CHILD; i++) {
        event_stack[i].state = 0;
    }
}


int volatile emergency_exit = 0;

void handle_chat(struct event_from_main_thread_data *event_data)
{
    printf("msg: %s", event_data->text);

}

void* handle_routine(void *data_join)
{
    socklen_t len;


    dprint("recv data after subthread %p\n", &data_join);
    struct data_join *detached_data = data_join;
    int server_by = detached_data->event_data.serve_by;
    logp("pesan: %s\n", detached_data->event_data.text);

    len = sizeof(detached_data->event_data.clientdata);

   //sendto(detached_data->event_from_main_thread_data.fd, "apa wkwk\n", 9, MSG_WAITALL, (struct sockaddr*)&detached_data->event_data.clientdata, len);

    //handle_chat(struct event_data *event_data);
    // carrier_now = (struct carrier*)carrier;
    // printf("breakpoint anyar %d\n", 999);
    // printf("breakpoint serv by %d\n", carrier_now->event_data->serve_by);
    // //handle_chat((struct event_data*)carrier_now->event_data);
    

    // // release the state
    // carrier_now->event_stack[carrier_now->event_data->serve_by]->state = 0;
    //printf("served by num %d\n", detached_data->event_data.serve_by);
    
    sleep(5);
    detached_data->event_stack[server_by].state = 0;

    
    
}

int random_thread_create(struct event_stack* event_stack, struct event_from_main_thread_data event_data)
{
    //printf("eventdata addr after %p\n", &event_data);
    struct data_join data_join;
    

    //printf("eventstack addr after %p\n", data_join.event_stack);
    // event_stack[0].state = 1;

    // return 0;
    // printf("creating state %d time %lu value %s", 
    //     data_join.event_stack[9]->state, 
    //     data_join.event_data.time, 
    //     data_join.event_data.text
    // );

    // data_join.event_stack[0]->state = 0;
    // printf("creating %d threads %lu | %s", data_join.event_stack[0]->state, data_join.event_data->time, data_join.event_data->text);


    // event_stack[0].state = 1;
    

    // struct carrier carrier;
    // printf("breakpoint 827a %d\n", 999);
    //printf("creating %d threads %lu | by %d data %s\n", data_join.event_stack[0]->state, data_join.event_data.time, data_join.event_data.serve_by, data_join.event_data.text);
    //printf("not %s\n", (data_join.event_stack[1]->state == 0) ? "true" : "false");
    //printf("showoff %d\n", data_join.event_stack[1]->state);

    for(int a = 0; a < MAX_CHILD; a++) {
        //printf("loop ke %d\n", a);
        if (event_stack[a].state == 0) {
            event_data.serve_by = a;
            event_stack[a].state = 1;
            dprint("befoore thread served by %d\n", event_data.serve_by);

            data_join.event_data  = event_data; // passed by reference
            data_join.event_stack = event_stack; // passed with detach

            // printf("datajoin memaddr di subthread %p\n", data_join);

            dprint("threads serve by %d status %d text %s\n", event_data.serve_by, event_stack[a].state, event_data.text);
            
            pthread_create(&event_stack[a].thread, 
                NULL, handle_routine, 
                (void*)&data_join); // copy data 
            return 0;
        } 
    }
    return -1;
    //         

            
    //     }   
    // }
    //     // cheching state
    //     printf("loopn %d\n", a);
    //     printf("state saat ini %d\n", event_stack[8].state);
    //     printf("breakpointku %d\n", 999);
    //     if (event_stack[a].state == 0) {
    //         event_data->serve_by = a;
    //         event_stack[a].state = 1; // change state
    //         carrier.event_stack = &event_stack;
    //         carrier.event_data = event_data;

    //         printf("threads serve by %d", event_data->serve_by);

    //         pthread_create(&event_stack[a].thread, NULL, handle_routine, (void*)&carrier);
    //         return a;
    //     } 
    // }
    return -1; // no enough child
}


void signal_handler(int signal_recv_number)
{
    printf("we've got %d signal, exiting\n", signal_recv_number);
    emergency_exit = 1;
}

void do_eventloop(struct garbage_descriptor *garbage_descriptor, pthread_t *handle_conn_thread)
{
    while(1){
        sleep(1);
        
        printf("udpfd memaddr afterpass %p\n", garbage_descriptor->udpfd);
        // checking
        if (emergency_exit == 1) {
            close(*garbage_descriptor->udpfd);
            close(*garbage_descriptor->epfd);
            //free(garbage_descriptor->events) ;
            pthread_cancel(*handle_conn_thread);
            pthread_join(*handle_conn_thread, NULL);
            printf("exit succesfully\n");
            break;
        }
    }
}



#define pthread_stack_state_reset pthread_stack_state_reset
void *handle_incoming_conn(void *ptr)
{
    
    int epoll_offset;
    int i;
    char buf[4096];

    struct garbage_descriptor *garbage_descriptor = ptr;
    struct epoll_event *events = garbage_descriptor->events;
    struct event_stack event_stack[10];
    struct event_from_main_thread_data event_data;
    struct sockaddr_in clientAddress;
    

    pthread_stack_state_reset(event_stack);

    while (1)
    {
        printf("waiting \n");
        epoll_offset = epoll_wait(*garbage_descriptor->epfd, events, EPOLL_MAX_EVENTS, -1);

        printf("offset %d \n", epoll_offset);

        for (i = 0; i < epoll_offset; i++) {
            printf("EPOLLERR %s EPOLLHUB %s EPOLLIN %s", (events[i].events & EPOLLERR) ? "true" : "false", 
                (events[i].events & EPOLLHUP) ? "true" : "false", 
                (events[i].events & EPOLLIN) ? "true" : "false");

            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || !(events[i].events & EPOLLIN)) {
                perror("epoll error");
                close(events[i].data.fd);
                continue;
            } else {
                printf("revc data zu zu zu %zu\n", sizeof(buf));
                memset(&buf, 0, sizeof(buf));
                memset(&event_data, 0, sizeof(event_data));
                recvfrom(events[i].data.fd, &buf, sizeof(buf), 0, 
                    (struct sockaddr *)&clientAddress, (socklen_t *)sizeof(clientAddress));

                event_data.time = (int)time(NULL);
                strcpy(event_data.text, buf);
                // event_data.ip = clientAddress.sin_addr;
                // printf("value \"%d\" \"%s\" \n", strcmp(buf, "gau"), buf);
                printf("revc data %s\n", buf);
                

                event_data.fd = &events[i].data.fd;
                event_data.clientdata = clientAddress;

                printf("memaddr %p \n", &clientAddress);
                printf("memaddr then %p \n", &event_data.clientdata);

                // if (random_thread_create(event_stack, event_data) == -1) {
                //     printf("[WARNING] waiting conn\n");
                // }
            }
        }
   }

    // socklen_t socklen = sizeof(clientAddress);
    // while (1)
    // {
    //     epoll_offset = epoll_wait(*epfd, events, EPOLL_MAX_EVENTS, 0);
        
    //     memset(&buf, 0, sizeof(buf));
    //     memset(&event_data, 0, sizeof(event_data));
    //     recvfrom(*udp_fd, &buf, sizeof(buf), 0, (struct sockaddr *)&clientAddress, (socklen_t *)sizeof(clientAddress));
    //     // printf("udp recvbuf: %s", buf);

    //     event_data.time = (int)time(NULL);
    //     strcpy(event_data.text, buf);
    //     event_data.ip = clientAddress.sin_addr;

        

    //     // printf("value \"%d\" \"%s\" \n", strcmp(buf, "gau"), buf);
    //     // return 0;
        
    //     if (strcmp(buf, "") != 0) {
    //         if (random_thread_create(event_stack, event_data) == -1) {
    //             printf("[WARNING] waiting conn\n");
    //         }
    //     } else {
    //         //printf("text null\n");
    //     }
    // }
}
#undef pthread_stack_state_reset

static int prepare_sockfd(int *udpfd_ptr, char *addr, int port, int is_nonblock)
{
    int sock_type, err, ret;
    int udpfd;

    struct sockaddr_in sockaddr_in;

    if (is_nonblock == 1) {
        sock_type = SOCK_DGRAM | SOCK_NONBLOCK;
    } else {
        sock_type = SOCK_DGRAM;
    }

    *udpfd_ptr = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    if (*udpfd_ptr == -1) {
        err = errno;
        perror("socket() error");
        return err;
    }
    
    memset(&sockaddr_in, 0, sizeof(sockaddr_in));

    sockaddr_in.sin_family = AF_INET;
    sockaddr_in.sin_port = htons(7000);
    sockaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    
    ret = bind(*udpfd_ptr, (const struct sockaddr*) &sockaddr_in, sizeof(sockaddr_in));
    if (ret == -1) {
        err = errno;
        perror("bind() error");
        close(*udpfd_ptr);
        return err;
    }
    return 0;

}

static int epoll_section(int *epfd, int *fd_to_watch, struct epoll_event *event)
{
    *epfd = epoll_create1(0);
    if (*epfd == -1) {
        perror("epoll_create1() error");
        return errno;
    }

    event->events = EPOLLIN;
    event->data.fd = *fd_to_watch;

    if (epoll_ctl(*epfd, EPOLL_CTL_ADD, *fd_to_watch, event) == -1) {
        perror("epoll_ctl() error");
        close(*epfd);
        return errno;
    }
    return 0;
}

int create_udp_server() 
{
    signal(SIGINT, signal_handler);

    int udpfd;
    int ret;
    int epfd;

    struct sockaddr_in sockaddr_in;
    struct garbage_descriptor garbage_descriptor;
    struct epoll_event event, events[EPOLL_MAX_EVENTS];

    pthread_t handle_conn_thread;

    ret = prepare_sockfd(&udpfd, "127.0.0.1", 7000, 1);
    if (ret != 0) {
        strerror(ret);
        goto exit_failure;
    }    

    ret = epoll_section(&epfd, &udpfd, &event);
    if (ret != 0) {
        strerror(ret);
        goto exit_failure;
    }

    // set all garbage to be cleaned
    garbage_descriptor.udpfd = &udpfd;
    garbage_descriptor.epfd = &epfd;
    garbage_descriptor.events = events;

    pthread_create(&handle_conn_thread, NULL, handle_incoming_conn, (void*)&garbage_descriptor);

    printf("epfd memaddr %d\n", epfd);
    printf("epfd memaddr struct %p\n", &garbage_descriptor.epfd);

    do_eventloop(&garbage_descriptor, &handle_conn_thread);
exit_failure:
    exit(EXIT_FAILURE);
}