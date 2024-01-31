//
// Created by Adrián on 30. 1. 2024.
//

#include <sys/socket.h>
#include <netinet/in.h>

struct Client
{
    int domain;
    int service;
    int protocol;
    int port;

    struct sockaddr_in address;

    int socket;

    void (*launch)(struct Client *client);
};

struct Client client_constructor(int domain, int service, int protocol, int port, void(*launch)(struct Client *client));