#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "core/config.h"
#include "core/security.h"

#define CONFIG_PATH "client.config"
#define BUFFER_LENGTH 1024

int main()
{
    printf("INFO >> Checking...\n");
    if (check_DEP() != 1)
    {
        perror("ERROR >> Enable DEP(NX) to run this application");
        exit(EXIT_FAILURE);
    }
    if (drop_root_privilegies() != 1)
    {
        perror("ERROR >> Unable to drop root privilegies");
        exit(EXIT_FAILURE);
    }

    printf("Reading conf ...\n");
    // Reading configuration
    char *addr = get_config_str_value(CONFIG_PATH, "ADDR");
    int port = get_config_int_value(CONFIG_PATH, "PORT");
    printf("Server address = %s\n", addr);
    printf("Server port = %i\n", port);

    // Setup connection
    printf("Connecting...\n");
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, addr, &serv_addr.sin_addr);

    // Connecting
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0)
    {
        printf("Connected !\n");
        while (1)
        {
            // Take input from user
            char message[BUFFER_LENGTH];
            printf("\nType time format you want:\n");
            fgets(message, BUFFER_LENGTH, stdin);

            // Send message to server
            if (send(sock, message, BUFFER_LENGTH, 0) == -1)
            {
                perror("SERVER >> Error sending");
                exit(EXIT_FAILURE);
            }
            printf("Format request: %s\n", message);

            // Get answer from server
            char buffer[BUFFER_LENGTH];
            valread = read(sock, buffer, BUFFER_LENGTH);
            if (valread == -1)
            {
                perror("Error reading");
                exit(EXIT_FAILURE);
            }
            buffer[valread] = '\0';

            // Print answer to clinet
            printf("Server answer: %s\n", buffer);
        }
    }
    else
        printf("Error connecting ! Try again\n");
    return 0;
}
