#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "core/config.h"
#include "core/security.h"
#include "server/server.h"
#include "server/console.h"

#define CONFIG_PATH "server.config"

void *server()
{
    // Read configuration parameters
    printf("SERVER >> Reading conf ...\n");
    int max_cli = get_config_int_value(CONFIG_PATH, "MCLI");
    int port = get_config_int_value(CONFIG_PATH, "PORT");
    printf("SERVER >> Server port = %i\n", port);
    printf("SERVER >> Server max number of clients = %i\n", max_cli);

    // Start server
    start_server(port, max_cli);
}

void *console_input()
{
    // Start console reading
    start_console();
}

int main(int argc, char const *argv[])
{
    // Check security
    if (check_DEP() != 0)
        perror("WARNING >> DEP(NX) is not enabled !");
    if (drop_privilegies() != 0)
        perror("WARNING >> Can't drop privileges !");
    if (argc == 1)
    {
        printf("INFO >> Starting...\n");

        // Create server listening thread
        pthread_t server_thread_id;
        pthread_create(&server_thread_id, NULL, server, NULL);

        // Create console listening thread
        pthread_t console_thread_id;
        pthread_create(&console_thread_id, NULL, console_input, NULL);

        // Wait for threads to end
        printf("INFO >> Application ready!\n");
        pthread_join(server_thread_id, NULL);
        pthread_join(console_thread_id, NULL);

        printf("INFO >> Appliction cleared!\n");
        return 0;
    }
    else
    {
        printf("To many arguments\n");
        return 1;
    }
}
