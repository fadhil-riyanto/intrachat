#ifndef _SERVER_H_
#define _SERVER_H_

#include <pthread.h>
#include <netinet/in.h>
#include <stdint.h>

struct event_data {
    int64_t time;
    char text[4096];
    struct in_addr ip;
    int serve_by;// whats thread number
};

struct event_stack
{
    pthread_t thread;
    int state;
};

struct data_join
{
    struct event_stack *event_stack;
    struct event_data event_data;
};

void signal_handler(int signal_recv_number);
void do_eventloop(int *udpfd, pthread_t *handle_conn_thread);
void *handle_incoming_conn(void *ptr);
int create_udp_server();

#endif