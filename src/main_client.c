#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "core/config.h"

#define CONFIG_PATH "client.config"

int main() {
    printf("Reading conf ...\n");
    char* addr = get_config_str_value(CONFIG_PATH, "ADDR");
    int port = get_config_int_value(CONFIG_PATH, "PORT");
    printf("Server address = %s\n", addr);
    printf("Server port = %i\n", port);

    printf("Connecting...\n");
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, addr, &serv_addr.sin_addr);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0) {
        printf("Connected !\n");
        while(1) {
            int message_length = 20;
            char message[message_length];
            printf("\nType time format you want:\n");
            scanf("%19s", message);

            send(sock, message, message_length, 0);
            printf("Format request: %s\n", message);

            int buffer_length = 1024;
            char buffer[buffer_length];
            valread = read(sock, buffer, 1024);
            printf("Server answer: %s\n", buffer);
        }
    } else
        printf("Error connecting ! Try again\n");
    return 0;
}
