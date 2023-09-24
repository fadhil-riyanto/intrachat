#ifndef _SERVER_H_
#define _SERVER_H_

#include <pthread.h>
#include <netinet/in.h>
#include <stdint.h>
#include <sys/epoll.h>

struct event_from_main_thread_data {
    int thread_num;
    
    int64_t time;
    char text[4096];
    struct in_addr ip;
    int serve_by;// whats thread number
    int fd; // fd to communicate
    struct sockaddr_in clientdata;

};

struct event_stack
{
    pthread_t thread;
    int state;
    int ready_to_use;
    int reuse;
};

struct data_join
{
    struct event_stack *event_stack;
    struct event_from_main_thread_data event_data;
};

struct garbage_descriptor
{
    int *udpfd;
    int *epfd;
    int *pthreadfd;
    struct epoll_event *event, *events;
    struct event_stack *event_stack;
};

void signal_handler(int signal_recv_number);
void do_eventloop(struct garbage_descriptor *garbage_descriptor, pthread_t *handle_conn_thread);
void *handle_incoming_conn(void *ptr);
int create_udp_server();
void pthread_stack_state_reset(struct event_stack *event_stack);

#endif