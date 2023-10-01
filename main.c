#include <asm-generic/errno-base.h>

#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"

#define getopt_required_arg 1
#define getopt_optional_arg 2

static const struct option long_options[] = {
    {"addr",    getopt_required_arg,NULL,'a'},
    {"port",    getopt_required_arg,NULL,'p'},
    {NULL,      0,                  0,   0}
};

void show_help()
{
    char help[1024] = "intrachat help\n\n" \
                        "--addr: set server listen (required)\n" \
                        "--port: set server listen port (required)\n" \
                        "\n\n" \
                        "example: ./server --addr 127.0.0.1 --port 9000\n";

    printf("%s", help);
}


int _try_parse(int argc, char *argv[], struct server_parameter* server_parameter)
{
    int ret;
    int longindex;

    ret = getopt_long(argc, argv, "a:p", long_options, &longindex);
    //printf("ret %c", ret);
    if (ret == -1) {
        printf("server addr and port is required\n");
        show_help();
        exit(-1);
    }
    switch (ret) {
        case 'a':
            server_parameter->addr = optarg;
            break;
        case 'p':
            server_parameter->port = optarg;
            break;
        case 'b':
            server_parameter->is_nonblock = optarg;
            break;
        default:
            printf("unknown option for %s\n", optarg);
            return EINVAL;
    }

    // if (!server_parameter->port && !server_parameter->port) {
    //     printf("server addr and port is required");
    //     exit(EXIT_FAILURE);
    // }
    return 0;
}

void try_parse(int argc, char *argv[], struct server_parameter* server_parameter)
{
    for(int i = 0; i < 2; i++) {
        _try_parse(argc, argv, server_parameter);
    }
}


void* callme(void *ptr)
{
    sleep(5);
    printf("hi im fadhil");
}

int main(int argc, char *argv[])
{
    struct server_parameter server_parameter = {NULL, NULL, NULL};

    try_parse(argc, argv, &server_parameter);

    printf("starting at %s:%s", server_parameter.addr, server_parameter.port);
    create_udp_server(&server_parameter, callme);

    
    return  0;
}