//
// Created by Adrián on 29. 1. 2024.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "client.h"

#define PORT 8888

void launch(struct Client *client)
{
    FILE *file = fopen("test.txt", "wb"); // change filename with name to be saved as
    char buffer[1024];
    ssize_t bytes;

    while((bytes = recv(client->socket, buffer, 1024, 0)) > 0)
    {
        if (fwrite(buffer, 1, bytes, file))
        {
            break;
        }
    }

    if (bytes <= 0)
    {
        perror("Error occured while receiving data\n");
        exit(1);
    }

    printf("Successfully downloaded\n");

    fclose(file);
    close(client->socket);
}

int main()
{
    struct Client client = client_constructor(AF_INET, SOCK_STREAM, 0, PORT, launch);
    client.launch(&client);
    return 0;
}