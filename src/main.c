#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "time.h"

void* console_input()
{
    while(1) {
        int buffer_length = 20;
        char buffer[buffer_length];

        printf("CONSOLE>> Enter date format:\n");
        scanf("%19s", buffer);

        printf("CONSOLE>> Time: %s\n", get_time(buffer));
    }
}

void* server()
{

}

int main(int argc, char const *argv[])
{
    // Create server listening thread
    printf("INFO >> Starting server ...\n");
    pthread_t server_thread_id;
    pthread_create(&server_thread_id, NULL, server, NULL);

    // Create console listening thread
    printf("INFO >> Starting console ...\n");
    pthread_t console_thread_id;
    pthread_create(&console_thread_id, NULL, console_input, NULL);

    // Wait for threads to end
    printf("INFO >> Application ready\n");
    pthread_join(server_thread_id, NULL);
    pthread_join(console_thread_id, NULL);

    printf("INFO >> Appliction cleared\n");
    return 0;
}
