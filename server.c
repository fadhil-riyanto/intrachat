#include "config.c"
#include "server.h"
#include "utils.h"

#include <assert.h>
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

int volatile emergency_exit = 0;
int volatile highest_pthread_reached = 0;

void server_set_properties(int port, char* address, int is_nonblock, 
    void *(*routine)(void*))
{

}

void pthread_stack_state_reset(struct event_stack *event_stack)
{
    for(int i = 0; i < MAX_CHILD; i++) {
        event_stack[i].state = 0;
        event_stack[i].ready_to_use = 1;
    }
}

void thread_joiner(struct event_stack *event_stack)
{

    for(int i = 0; i <= highest_pthread_reached; i++) {
        //printf("state %d\n", event_stack[i].state);
        // to do next: check 10 thread state, cancel 10 thread
        if (event_stack[i].state == 0 && event_stack[i].ready_to_use == 0) {
            printf("joiner cleaning thread %d\n", i);
            pthread_join(event_stack[i].thread, NULL);
            event_stack[i].ready_to_use = 1;
        }
    }

    
}

void handle_chat(struct event_from_main_thread_data *event_data)
{
    printf("msg: %s", event_data->text);

}

void* handle_routine(void *data_join)
{
    struct data_join *detached_data = data_join;
    int serve_by = *detached_data->serve_by;
    char text[MAXIMUM_BUFFER];
    //strcpy(text, detached_data->event_data[serve_by].text);
    sleep(5);
    // dprint("recv data after subthread %p\n", &data_join);
    // printf("nums\n");
    // printf("nums %d\n", *(int*)data_join);
    
    printf("incoming messange adalah %s\n", detached_data->event_data[serve_by].text);
    //int serve_by = detached_data->serve_by;
    // int server_by = detached_data->event_data.serve_by;
    

    //detached_data->event_data[serve_by].routine(NULL);
    // socklen_t len = sizeof(detached_data->event_data.clientdata);
    // char msg[1024];
    // //sprintf(msg, "\nyour_messange: %stimestamp: %lu\nserve_by_thread_num:%d\n", 
    // //    detached_data->event_data[serve_by].text, detached_data->event_data[serve_by].time, *detached_data->serve_by);
    // sprintf(msg, "[server] apa? kok bilang \"%s\"", detached_data->event_data[serve_by].text);

    // int ret = sendto(
    //     detached_data->event_data[serve_by].fd, 
    //     msg, strlen(msg),
    //     0, (struct sockaddr*)&detached_data->event_data[serve_by].client_addr, sizeof(detached_data->event_data[serve_by].client_addr));
    // memset(msg, 0, sizeof(msg));
    //sprintf(msg, "\nyour_messange: %stimestamp: %lu\nserve_by_thread_num:%d\n", 
    //    detached_data->event_data[serve_by].text, detached_data->event_data[serve_by].time, *detached_data->serve_by);
    // sprintf(msg, "%s ", "[you] >");

    // ret = sendto(
    //     detached_data->event_data[serve_by].fd, 
    //     msg, strlen(msg),
    //     0, (struct sockaddr*)&detached_data->event_data[serve_by].client_addr, sizeof(detached_data->event_data[serve_by].client_addr));
    

//    sendto(detached_data->event_data, "apa wkwk\n", 9, MSG_WAITALL, (struct sockaddr*)&detached_data->event_data[serve_by].client_addr, len);

    //handle_chat(struct event_data *event_data);
    // carrier_now = (struct carrier*)carrier;
    // printf("breakpoint anyar %d\n", 999);
    // printf("breakpoint serv by %d\n", carrier_now->event_data->serve_by);
    // //handle_chat((struct event_data*)carrier_now->event_data);
    

    // // release the state
    // carrier_now->event_stack[carrier_now->event_data->serve_by]->state = 0;
    //printf("served by num %d\n", detached_data->event_data.serve_by);
    //logp("pesan: %s\n", detached_data->event_data[serve_by].text);
    //sleep(5);
    
    //close(detached_data->event_data.fd);
    //detached_data->event_stack[serve_by].state = 0;
    detached_data->event_stack[serve_by].state = 0;
}

int random_thread_create_get_freenums(struct event_stack* event_stack) 
{
    for(int a = 0; a < MAX_CHILD; a++) {
        if (event_stack[a].state == 0 && event_stack[a].ready_to_use == 1) {
            return a;
        }
    }
    return -1;
}

int random_thread_create(struct data_join *data_join, 
    struct event_stack* event_stack, 
    struct event_from_main_thread_data *event_data, int *free_thread_nums)
{

    
    event_stack[*free_thread_nums].state = 1;
    event_stack[*free_thread_nums].ready_to_use = 0;
    // dprint("befoore thread served by %d\n", free_thread_nums);

    // printf("eventstack memaddr %p\n", &event_stack);

    data_join->event_data  = event_data;
    data_join->event_stack = event_stack;
    data_join->serve_by = free_thread_nums;

    

    

    // printf("datajoin memaddr di subthread %p\n", data_join);

    dprint("threads serve by %d andstatus %d text %s\n", *free_thread_nums, event_stack[*free_thread_nums].state, event_data[*free_thread_nums].text);
    
    printf("free thread now is %d\n", *data_join->serve_by);

    int squahnum = 890;
    pthread_create(&event_stack[*free_thread_nums].thread, 
        NULL, handle_routine, 
        (void*)data_join); // copy data 

    //sleep(1);

    // printf("quahnum after %d\n", squahnum);
    if (*free_thread_nums > highest_pthread_reached)
    {
        highest_pthread_reached = *free_thread_nums;
    }
    return 0;
}


void signal_handler(int signal_recv_number)
{
    printf("we've got %d signal, exiting\n", signal_recv_number);
    emergency_exit = 1;
}

void do_eventloop(struct main_thread_carrier *main_thread_carrier, pthread_t *handle_conn_thread)
{
    //printf("[thread] after memaddr struct %p\n", handle_conn_thread);
    while(1){
        sleep(1);
        thread_joiner(main_thread_carrier->event_stack);
        
        printf("udpfd memaddr afterpass %p\n", main_thread_carrier->udpfd);
        // checking
        if (emergency_exit == 1) {
            printf("higest reached %d\n", highest_pthread_reached);
            
            for(int i = 0; i <= highest_pthread_reached; i++) {

                // to do next: check 10 thread state, cancel 10 thread
                if (main_thread_carrier->event_stack[i].state == 1) {
                    printf("killing running thread %d\n", i);
                    pthread_cancel(main_thread_carrier->event_stack[i].thread);
                }

                if (main_thread_carrier->event_stack[i].ready_to_use == 0) {
                    printf("clening the unclean thread %d\n", i);
                    pthread_join(main_thread_carrier->event_stack[i].thread, NULL);
                }
                
                
                
            }

            pthread_cancel(*handle_conn_thread);
            pthread_join(*handle_conn_thread, NULL);

            close(*main_thread_carrier->udpfd);
            close(*main_thread_carrier->epfd);

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
    int rand_thread_ret;
    char buf[1024];

    struct main_thread_carrier *main_thread_carrier = ptr;
    struct epoll_event *events = main_thread_carrier->events;
    struct event_stack *event_stack = main_thread_carrier->event_stack;
    struct event_from_main_thread_data event_data[MAX_CHILD];
    struct sockaddr_in client_addr;
    struct data_join data_join;


    pthread_stack_state_reset(event_stack);

    while (1)
    {
        printf("waiting \n");
        epoll_offset = epoll_wait(*main_thread_carrier->epfd, events, EPOLL_MAX_EVENTS, -1);

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

                socklen_t slen = sizeof(client_addr);

                memset(&buf, 0, sizeof(buf));
                //memset(&event_data, 0, sizeof(event_data));
                recvfrom(*main_thread_carrier->udpfd, &buf, sizeof(buf), 0, 
                    (struct sockaddr *)&client_addr, &slen);

                rand_thread_ret = random_thread_create_get_freenums(event_stack);
                if (rand_thread_ret == -1) {
                    printf("[WARNING] waiting conn\n");
                } else {
                    event_data[rand_thread_ret].fd = events[i].data.fd;
                    event_data[rand_thread_ret].time = (int)time(NULL);
                    strcpy(event_data[rand_thread_ret].text, buf);
                    //strcpy(event_data[rand_thread_ret].text, buf);
                    event_data[rand_thread_ret].client_addr = client_addr;
                    event_data[rand_thread_ret].routine = main_thread_carrier->routine;

                    random_thread_create(&data_join, event_stack, event_data, &rand_thread_ret);

                    //printf("data recv adlah %s\n", event_data[rand_thread_ret].text);
                }

                // event_data[].time = ;
                // strcpy(event_data.text, buf);
                // // event_data.ip = clientAddress.sin_addr;
                // // printf("value \"%d\" \"%s\" \n", strcmp(buf, "gau"), buf);
                // dprint("revc data %s\n", buf);
                

                // event_data.fd = events[i].data.fd;
                // event_data.clientdata = clientAddress;
                // event_data.routine = main_thread_carrier->routine;

                
            }
        }
   }
}
#undef pthread_stack_state_reset

static int prepare_sockfd(int *udpfd_ptr, char *addr, int port, int is_nonblock)
{
    int sock_type, err, ret;

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
    sockaddr_in.sin_port = htons(port);
    sockaddr_in.sin_addr.s_addr = INADDR_ANY;
    
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

int create_udp_server(struct server_parameter* server_parameter, void *(*routine)(void*)) 
{
    signal(SIGINT, signal_handler);

    int udpfd;
    int ret;
    int epfd;

    
    struct epoll_event event, events[EPOLL_MAX_EVENTS];
    struct event_stack event_stack[10];

    pthread_t handle_conn_thread;

    ret = prepare_sockfd(&udpfd, server_parameter->addr, 
        atoi(server_parameter->port), 
        1);

    if (ret != 0) {
        strerror(ret);
        exit(EXIT_FAILURE);
    }    

    ret = epoll_section(&epfd, &udpfd, &event);
    if (ret != 0) {
        strerror(ret);
        exit(EXIT_FAILURE);
    }

    // set all garbage to be cleaned

    struct main_thread_carrier main_thread_carrier = {
        &udpfd, &epfd, events, event_stack, routine
    };
    

    pthread_create(&handle_conn_thread, NULL, handle_incoming_conn, (void*)&main_thread_carrier);

    //printf("epfd memaddr %d\n", epfd);
    //printf("[thread] memaddr struct %p\n", &handle_conn_thread);

    do_eventloop(&main_thread_carrier, &handle_conn_thread);
    return 0;
}