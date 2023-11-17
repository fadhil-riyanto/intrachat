#ifndef CHAT_SESSION_HANDLER_H_
#define CHAT_SESSION_HANDLER_H_

#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct messange_input_properties
{
    char *command;
    char *value[];
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