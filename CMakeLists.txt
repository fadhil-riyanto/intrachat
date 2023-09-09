cmake_minimum_required(VERSION 3.27.1)

PROJECT(server)

SET(source
    server.c
    server.h
)


add_library(sourcelib STATIC "${source}")
add_executable(mainsource main.c)

target_link_libraries(mainsource sourcelib)

set_target_properties(mainsource PROPERTIES OUTPUT_NAME "server")
