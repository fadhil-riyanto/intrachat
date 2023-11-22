cmake_minimum_required(VERSION 3.27.1)
add_compile_options(-Wall -Wextra -Wpedantic)


PROJECT(server)

SET(source
    server.c
    utils.c
    db/keyvalue_db.c
    db/keyvalue_db.h
    chat/chat_session_handler.c
    chat/chat_session_handler.h
    chat/utils/json_parsing.c
)


add_library(sourcelib STATIC "${source}")
add_executable(mainsource main.c)

target_link_libraries(mainsource sourcelib json-c)

set_target_properties(mainsource PROPERTIES OUTPUT_NAME "server")
