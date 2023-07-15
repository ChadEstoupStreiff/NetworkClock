#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"

#define MAX_COMMAND_BUFFER_LENGTH 1024
#define MAX_COMMAND_LENGTH 7

int get_command(char *buffer, char *command_buffer)
{
    if (buffer[0] == ' ')
        return 0;

    for (int i = 0; i < MAX_COMMAND_LENGTH; i++)
    {
        if (buffer[i] == ' ' || buffer[i] == '\0' || buffer[i] == '\n')
        {
            command_buffer[i] = '\0';
            return i;
        }
        command_buffer[i] = buffer[i];
    }

    return MAX_COMMAND_LENGTH;
}

int get_arg(char *buffer, int command_length, char *arg_buffer)
{
    if (buffer[command_length + 1] == ' ' || buffer[command_length + 1] == '\0' || buffer[command_length + 1] == '\n')
        return 0;

    for (int i = command_length + 1; i < MAX_COMMAND_BUFFER_LENGTH; i++)
    {
        if (buffer[i] == '\0' || buffer[i] == '\n')
        {
            arg_buffer[i - command_length - 1] = '\0';
            return i - command_length - 1;
        }
        arg_buffer[i - command_length - 1] = buffer[i];
    }
    return MAX_COMMAND_LENGTH - command_length - 1;
}

void start_console()
{
    char buffer[MAX_COMMAND_BUFFER_LENGTH];
    while (1)
    {

        printf("CONSOLE >> Enter command:\n");
        fgets(buffer, MAX_COMMAND_BUFFER_LENGTH, stdin);

        char *command = malloc(sizeof(char) * MAX_COMMAND_LENGTH);
        int command_length = get_command(buffer, command);

        if (command_length > 0)
        {
            if (strcmp(command, "time") == 0)
            {
                char *arg = malloc(sizeof(char) * (MAX_COMMAND_LENGTH - command_length - 1));
                int arg_length = get_arg(buffer, command_length, arg);

                char *time;
                if (arg_length == 0)
                    time = get_time("%F %r");
                else
                    time = get_time(arg);

                printf("CONSOLE >> Time: %s\n", time);
            }
            else if (strcmp(command, "settime") == 0)
            {
                char *arg = malloc(sizeof(char) * (MAX_COMMAND_LENGTH - command_length - 1));
                int arg_length = get_arg(buffer, command_length, arg);

                char *time;
                if (arg_length == 0)
                    printf("CONSOLE >> Please, input a time to set!\n");
                else
                {
                    set_time(atoi(arg));
                    printf("CONSOLE >> Time set !\n");
                }
            }
            else
            {
                printf("CONSOLE >> Unknown command, try again!\n");
            }
        }

        // printf("CONSOLE>> Time: %s\n", get_time(buffer));
    }
}