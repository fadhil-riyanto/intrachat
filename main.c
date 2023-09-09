#include <stdio.h>
#include "server.h"

int main(int argc, char *argv[])
{
    printf("starting server\n");
    create_udp_server();
    return  0;
}