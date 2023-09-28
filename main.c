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
    {"nonblock",getopt_optional_arg,NULL,'b'},  
    {NULL,      0,                  0,   0}
};

int try_parse(int argc, char *argv[], struct server_parameter* server_parameter)
{
    int ret;
    int longindex;

    ret = getopt_long(argc, argv, "a:p:b", long_options, NULL);

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

    // if (server_parameter->addr == NULL || server_parameter->port == NULL) {
    //     printf("server port and addr is required");
    //     exit(EXIT_FAILURE);
    // }




}

void* callme(void *ptr)
{
    printf("hi im fadhil");
}

int main(int argc, char *argv[])
{
    struct server_parameter server_parameter = {NULL, NULL, NULL};

    try_parse(argc, argv, &server_parameter);
    create_udp_server(&server_parameter, callme);

    
    return  0;
}