#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"

#define MAX_COMMAND_BUFFER_LENGTH 1024
#define MAX_COMMAND_LENGTH 7

int get_command(char *buffer, char *command_buffer)
{
    // Check if doesn't start with space, instead, throw a command length of 0
    if (buffer[0] == ' ')
        return 0;

    // Will copy every car until space or end of input
    for (int i = 0; i < MAX_COMMAND_LENGTH; i++)
    {
        // If space or end of input return buffer and command length
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
    // Check if doesn't start with space, instead, throw an argument length of 0
    if (buffer[command_length + 1] == ' ' || buffer[command_length + 1] == '\0' || buffer[command_length + 1] == '\n')
        return 0;

    // Will copy every car until end of input
    for (int i = command_length + 1; i < MAX_COMMAND_BUFFER_LENGTH; i++)
    {
        // If end of input return buffer and command length
        if (buffer[i] == '\0' || buffer[i] == '\n')
        {
            arg_buffer[i - command_length - 1] = '\0';
            return i - command_length - 1;
        }
        arg_buffer[i - command_length - 1] = buffer[i];
    }
    arg_buffer[MAX_COMMAND_BUFFER_LENGTH - 1] = '\0';
    return MAX_COMMAND_LENGTH - command_length - 1;
}

void start_console()
{
    // Setup buffer
    char buffer[MAX_COMMAND_BUFFER_LENGTH];
    while (1)
    {
        // Get client input
        printf("CONSOLE >> Enter command:\n");
        fgets(buffer, MAX_COMMAND_BUFFER_LENGTH, stdin);

        // Setup space for command input
        char *command = malloc(sizeof(char) * MAX_COMMAND_LENGTH);
        int command_length = get_command(buffer, command);

        // If there is a command
        if (command_length > 0)
        {
            // If command is "time"
            if (strcmp(command, "time") == 0)
            {
                // Setup space for argument input and get argument
                char *arg = malloc(sizeof(char) * (MAX_COMMAND_BUFFER_LENGTH - command_length - 1));
                int arg_length = get_arg(buffer, command_length, arg);

                // If no argument, get default time format, instead give a formated current time
                char *time;
                if (arg_length == 0)
                    time = get_time("%F %r");
                else
                    time = get_time(arg);

                printf("CONSOLE >> Time: %s\n", time);
            }
            // If command is "settime"
            else if (strcmp(command, "settime") == 0)
            {
                // Setup space for argument input and get argument
                char *arg = malloc(sizeof(char) * (MAX_COMMAND_BUFFER_LENGTH - command_length - 1));
                int arg_length = get_arg(buffer, command_length, arg);

                // If no argument, print error, instead set time based on argument
                char *time;
                if (arg_length == 0)
                    printf("CONSOLE >> Please, input a time to set!\n");
                else
                {
                    if (set_time(arg) == 0)
                    {
                        printf("CONSOLE >> Time set !\n");
                    }
                    else
                    {
                        printf("CONSOLE >> Error setting time !\n");
                    }
                }
            }
            // If command is unknown
            else
            {
                printf("CONSOLE >> Unknown command, try again!\n");
            }
        }
    }
}