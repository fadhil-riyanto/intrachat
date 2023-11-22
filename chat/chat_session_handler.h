#ifndef CHAT_SESSION_HANDLER_H_
#define CHAT_SESSION_HANDLER_H_

#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct messange_input_properties
{
    char *command;
    char *p1;
    char *p2;
    char *p3;
    char *p4;
    char *p5;
    char *p6;
    char *p7;
    char *p8;
    char *p9;
    char *p10;
    char *p11;
    char *p12;
    char *p13;
    char *p14;
    char *p15;
    char *p16;
    char *p17;
    char *p18;
    char *p19;
    char *p20;
};

struct messange_input
{
    char *text;
    int length;
    int64_t time;
};

struct server
{
    int fd;
    struct sockaddr_in client_addr;
};

void* recv_callback_from_server(void* params);

#endif