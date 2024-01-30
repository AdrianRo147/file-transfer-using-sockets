//
// Created by Adrián on 29. 1. 2024.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"

void launch(struct Server *server)
{
    char buffer[1024];
    char *fileName = "server.h";
    FILE *file;
    file = fopen(fileName, "r");

    if (file == NULL)
    {
        perror("Cannot open file...\n");
        exit(1);
    }

    size_t fileSize = fread(buffer, 1, sizeof(buffer), file);
    int new_socket;
    int address_length = sizeof(server->adress);

    while (1) // server need to be running in endless loop
    {
        printf("====== WAITING FOR CONNECTION ======\n");
        new_socket = accept(server->socket, (struct sockaddr *)&server->adress, (socklen_t *)&address_length);
        read(new_socket, buffer, 1024);
        printf("%s\n", buffer);
        send(new_socket, buffer, fileSize, 0);
        close(new_socket);
        fclose(file);
    }
}

int main() {
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8888, 10, &launch);
    server.launch(&server);
}