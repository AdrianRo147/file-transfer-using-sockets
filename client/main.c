//
// Created by Adrián on 29. 1. 2024.
//

#include <stdio.h>
#include <unistd.h>
#include "client.h"

void launch(struct Client *client)
{
    FILE *file = fopen("test.txt", "wb");
    char buffer[1024];
    ssize_t bytes;
    while((bytes = recv(client->socket, buffer, 1024, 0)) > 0)
    {
        fwrite(buffer, 1, bytes, file);
    }

    if (bytes < 0)
    {
        perror("Error occured while receiving data\n");
    }

    printf("Successfully downloaded");

    fclose(file);
    close(client->socket);
}

int main()
{
    printf("1\n");
    struct Client client = client_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8888, launch);
    client.launch(&client);
    return 0;
}