#include "chat_session_handler.h"
#include "../server.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>


void* recv_callback_from_server(void* params) {
    struct data_join *detached_data = params;
    int serve_by = *detached_data->serve_by;

    struct messange_input messange_input = {
        detached_data->event_data[serve_by].text, 
        strlen(detached_data->event_data[serve_by].text),
        detached_data->event_data[serve_by].time
    };

    struct server server = {
        detached_data->event_data[serve_by].fd, 
        detached_data->event_data[serve_by].client_addr
    };

    char buf[1024];
    sprintf(buf, "recv_callback_from_server text %s with length %d on %lu at routine void *(*routine)(void*))\n", 
        messange_input.text, messange_input.length, messange_input.time);

    sendto(server.fd, &buf, sizeof(buf), 0, (struct sockaddr*)&server.client_addr, sizeof(server.client_addr));
    return 0;
}