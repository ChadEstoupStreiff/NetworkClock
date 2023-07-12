#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define ADDRESS "127.0.0.1"

int main() {
    printf("Connecting...\n");
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, ADDRESS, &serv_addr.sin_addr);
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

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

    return 0;
}
