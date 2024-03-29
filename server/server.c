//
// Created by Adrián on 29. 1. 2024.
//

#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define IP_ADRESS "0.0.0.0"

struct Server server_constructor(int domain, int service, int protocol, int port, int backlog, void (*launch)(struct Server *server))
{
    struct Server server;

    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.port = port;
    server.backlog = backlog;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);

    if (inet_pton(AF_INET, IP_ADRESS, &server.address.sin_addr) <= 0)
    {
        perror("Cannot set IP...\n");
        exit(1);
    }

    server.socket = socket(domain, service, protocol);

    if (server.socket == 0)
    {
        perror("Failed to connect to socket...\n");
        exit(1);
    }

    if (bind(server.socket, (struct sockaddr*)&server.address, sizeof(server.address)) < 0)
    {
        perror("Failed to bind socket...\n");
        exit(1);
    }

    if (listen(server.socket, server.backlog) < 0)
    {
        perror("Failed to start listening...\n");
    }

    printf("Server listening on port %d...\n", server.port);

    server.launch = launch;

    return server;
}