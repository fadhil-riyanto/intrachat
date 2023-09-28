#ifndef _SERVER_H_
#define _SERVER_H_

#include "config.c"
#include <pthread.h>
#include <netinet/in.h>
#include <stdint.h>
#include <sys/epoll.h>

struct event_from_main_thread_data {
    int fd; // fd from epoll
    int64_t time;
    char text[MAXIMUM_BUFFER];
    struct sockaddr_in client_addr;
    void    *(*routine)(void *);

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
    struct event_from_main_thread_data *event_data;
    struct event_stack *event_stack;
    int *serve_by;
};

/*
 * the struct that need to be cleaned by cleaner
*/

struct main_thread_carrier
{
    int *udpfd;
    int *epfd;
    struct epoll_event *events;
    struct event_stack *event_stack;
    void    *(*routine)(void *);
    
};

struct server_parameter
{
    char    *addr;
    char    *port;
    char    *is_nonblock;
};

void signal_handler(int signal_recv_number);
void do_eventloop(struct main_thread_carrier *main_thread_carrier, pthread_t *handle_conn_thread);
void *handle_incoming_conn(void *ptr);
int create_udp_server(struct server_parameter* server_parameter, void *(*routine)(void*));
void pthread_stack_state_reset(struct event_stack *event_stack);

#endif