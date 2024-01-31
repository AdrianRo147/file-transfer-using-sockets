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
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(struct Server *server);
};

struct Server server_constructor(int domain, int service, int protocol, int port, int backlog, void(*launch)(struct Server *server));