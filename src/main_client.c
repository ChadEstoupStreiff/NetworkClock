#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "core/config.h"

#define CONFIG_PATH "client.config"
#define BUFFER_LENGTH 1024

int main()
{
    printf("Reading conf ...\n");
    char *addr = get_config_str_value(CONFIG_PATH, "ADDR");
    int port = get_config_int_value(CONFIG_PATH, "PORT");
    printf("Server address = %s\n", addr);
    printf("Server port = %i\n", port);

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
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0)
    {
        printf("Connected !\n");
        while (1)
        {
            int message_length = 64;
            char message[message_length];
            printf("\nType time format you want:\n");
            scanf("%63s", message);

            if (send(sock, message, message_length, 0) == -1)
            {
                perror("SERVER >> Error sending");
                exit(EXIT_FAILURE);
            }
            printf("Format request: %s\n", message);

            char buffer[BUFFER_LENGTH];
            valread = read(sock, buffer, BUFFER_LENGTH);
            if (valread == -1)
            {
                perror("Error reading");
                exit(EXIT_FAILURE);
            }
            buffer[valread] = '\0';
            printf("Server answer: %s\n", buffer);
        }
    }
    else
        printf("Error connecting ! Try again\n");
    return 0;
}
