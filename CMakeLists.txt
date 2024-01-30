cmake_minimum_required(VERSION 3.22)
project(file_transfer_sockets_server C)

set(CMAKE_C_STANDARD 23)

add_executable(file_transfer_socket_server server/main.c server/server.c server/server.h)
add_executable(file_transfer_socket_client client/main.c
        client/client.h
        client/client.c)
