#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "time.h"

void start_server(int port, int max_clients)
{
    // Setup server variables
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        perror("SERVER >> Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Setup address config
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        perror("SERVER >> Error binding");
        exit(EXIT_FAILURE);
    }
    // Listen socket
    if (listen(server_fd, max_clients) == -1)
    {
        perror("SERVER >> Error listening");
        exit(EXIT_FAILURE);
    }

    printf("SERVER >> Server listening on port %d\n", port);

    int cliend_id = 0;
    while (1)
    {
        // Accept incoming connections
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket == -1)
        {
            perror("SERVER >> Error accepting connection");
            exit(EXIT_FAILURE);
        }
        cliend_id++;

        // Fork on any new connection to continue accepting connection while still answering to current connection
        printf("SERVER >> [CLIENT %i] New client connected\n", cliend_id);
        switch (fork())
        {
        case 0:
            do
            {
                // Read from connection
                char buffer[1024];
                valread = read(new_socket, buffer, 1024);
                if (valread == -1)
                {
                    perror("SERVER >> Error reading");
                    exit(EXIT_FAILURE);
                }
                buffer[valread] = '\0';
                printf("SERVER >> [CLIENT %i] Client time format request: %s\n", cliend_id, buffer);

                // Get time based on readed request
                char *answer;
                if (valread == 0 || strcmp(buffer, "time") == 0 || strcmp(buffer, "get") == 0 || strcmp(buffer, "default") == 0)
                    answer = get_time("%F %r");
                else
                    answer = get_time(buffer);

                // Send answer
                send(new_socket, answer, strlen(answer), 0);
                printf("SERVER >> [CLIENT %i] Answer: %s\n", cliend_id, answer);
            } while (valread > 0);

            // Close connection
            close(new_socket);
            printf("SERVER >> [CLIENT %i] Client disconnected\n", cliend_id);
        case -1:
            // Error
            close(new_socket);
            printf("SERVER >> [CLIENT %i] Error creating client processus, client disconnected\n", cliend_id);
        default:
        }
    }
}