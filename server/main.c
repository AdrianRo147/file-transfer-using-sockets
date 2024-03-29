//
// Created by Adrián on 29. 1. 2024.
//

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>
#include "server.h"

#define PORT 8888

void *sendFile(void *arg)
{
    int new_socket = *((int *)arg);

    FILE *file = fopen("server.h", "rb"); // change filename to filename you want to send
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
        ssize_t bytesSent = send(new_socket, buffer, bytesRead, 0);

        if (bytesSent == -1)
        {
            perror("Error occured while sending file...\n");
            exit(1);
        }

        totalBytesSend += bytesSent;

        if (totalBytesSend == fileSize)
        {
            printf("File sent...\n");
            break;
        }
    }

    fclose(file);
}

void launch(struct Server *server)
{
    int new_socket;
    int address_length = sizeof(server->address);

    const char* originalKey = "YOUR_AUTH_KEY"; // authentification key

    while (1)
    {
        new_socket = accept(server->socket, (struct sockaddr *) &server->address, (socklen_t *) &address_length);

        char authKey[1024]; // used for storing auth key received from client
        ssize_t recvBytes = recv(new_socket, authKey, sizeof(authKey), 0);

        authKey[recvBytes] = '\0'; // when sending from client to server the auth key doesn't have correctly null character at end for some reason

        if (strcmp(authKey, originalKey) != 0 || strlen(authKey) != strlen(originalKey)) // compares if keys matches with strcmp and strlen
        {
            fprintf(stderr, "Invalid key from client %s:%d\n", inet_ntoa(server->address.sin_addr), ntohs(server->address.sin_port));
            exit(1);
        }

        printf("File sent to %s:%d\n", inet_ntoa(server->address.sin_addr), ntohs(server->address.sin_port));

        pthread_t thread; // threads needed for handling multiple connections
        if (pthread_create(&thread, NULL, sendFile, &new_socket) != 0)
        {
            perror("Error creating thread...\n");
            close(new_socket);
            exit(1);
        }
    }
}

int main() {
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, PORT, 10, launch);
    server.launch(&server);
}