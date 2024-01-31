//
// Created by Adrián on 30. 1. 2024.
//

#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define IP_ADDRESS "127.0.0.1"

struct Client client_constructor(int domain, int service, int protocol, int port, void (*launch)(struct Client *client))
{
    struct Client client;

    client.domain = domain;
    client.service = service;
    client.protocol = protocol;
    client.port = port;

    client.address.sin_family = domain;
    client.address.sin_port = htons(port);

    if (inet_pton(AF_INET, IP_ADDRESS, &client.address.sin_addr) <= 0)
    {
        perror("Cannot set IP...\n");
        exit(1);
    }

    client.socket = socket(domain, service, protocol);

    if (client.socket == 0)
    {
        perror("Failed to connect to socket...\n");
        exit(1);
    }

    if (connect(client.socket, (struct sockaddr*)&client.address, sizeof(client.address)) < 0)
    {
        perror("Failed connecting to socket\n");
        close(client.socket);
        exit(1);
    }

    client.launch = launch;

    return client;
}