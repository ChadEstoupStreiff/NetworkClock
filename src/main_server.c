#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
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
    printf("INFO >> Checking...\n");
    if (check_DEP() != 0)
    {
        exit(EXIT_FAILURE);
    }
    if (drop_privilegies() != 0)
    {
        exit(EXIT_FAILURE);
    }
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
    else if (argc == 2)
    {
        if (enable_settime_capability() != 0)
        {
            exit(EXIT_FAILURE);
        }

        // Convert argument to long int
        long int new_time = atol(argv[1]);
        if (new_time <= 0)
            exit(EXIT_FAILURE);

        // Prepare variables to set time
        struct timeval tv;
        tv.tv_sec = new_time;
        tv.tv_usec = 0;

        // Set time
        if (settimeofday(&tv, NULL) < 0)
            exit(EXIT_FAILURE);

        return 0;
    }
    else
    {
        printf("To many arguments\n");
        return 1;
    }
}
