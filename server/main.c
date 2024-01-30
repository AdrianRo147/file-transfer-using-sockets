//
// Created by Adrián on 29. 1. 2024.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"

void sendFile(struct Server *server)
{
    FILE *file = fopen("server.h", "rb");
    if (!file)
    {
        perror("Cannot open file...\n");
        exit(1);
    }

    size_t fileSize = ftell(file);
    char buffer[1024];
    size_t bytesRead, totalBytesSend = 0;

    while ((bytesRead = fread(buffer, 1, 1024, file)) > 0)
    {
        ssize_t bytesSent = send(server->socket, buffer, bytesRead, 0);

        if (bytesSent == -1)
        {
            perror("Error occured while sending file...\n");
            exit(1);
        }

        totalBytesSend += bytesSent;

        if (totalBytesSend == fileSize)
        {
            break;
        }
    }

    fclose(file);
}

void launch(struct Server *server) // TODO: program exits after file is sent
{
    int new_socket;
    int address_length = sizeof(server->adress);

    printf("====== WAITING FOR CONNECTION ======\n");
    new_socket = accept(server->socket, (struct sockaddr *)&server->adress, (socklen_t *)&address_length);

    sendFile(server);
    printf("File sent...\n");

    close(new_socket);
}

int main() {
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8888, 10, launch);
    server.launch(&server);
}