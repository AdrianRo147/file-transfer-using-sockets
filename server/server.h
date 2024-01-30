//
// Created by Adrián on 29. 1. 2024.
//

#include <sys/socket.h>
#include <netinet/in.h>

struct Server
{
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in adress;

    int socket;

    void (*launch)(struct Server *server);
};

struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, void(*launch)(struct Server *server));