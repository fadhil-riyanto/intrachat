#ifndef _SERVER_H_
#define _SERVER_H_

#include <pthread.h>

void signal_handler(int signal_recv_number);
void do_eventloop(int *udpfd, pthread_t *handle_conn_thread);
void *handle_incoming_conn(void *ptr);
int create_udp_server();

#endif