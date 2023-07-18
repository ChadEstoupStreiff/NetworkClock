#include <stdio.h>
#define _XOPEN_SOURCE /* See feature_test_macros(7) */
#include <time.h>
#include <stdlib.h>

#define MAX_FORMATED_TIME_LENGTH 64
#define ADMIN_BUFFER_LENGTH 1024

char *get_time(char *format)
{
    // Get time info
    time_t rawtime = time(NULL);
    struct tm *timeinfo = localtime(&rawtime);

    // Create buffer
    char *buffer = malloc(sizeof(char) * MAX_FORMATED_TIME_LENGTH);

    // Format time info into buffer
    if (strftime(buffer, MAX_FORMATED_TIME_LENGTH, format, timeinfo) <= 0)
    {
        perror("ERROR >> Cannot format time");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

int set_time(char *time)
{
    // Read user input
    struct tm tm;
    if (strptime(time, "%F %T", &tm) != NULL)
    {
        // Convert time to seconds
        time_t t = mktime(&tm);

        // Creating command string
        char admin_buffer[ADMIN_BUFFER_LENGTH];
        sprintf(admin_buffer, "sudo ./settime_app %li", t);

        // Executing settime app
        printf("CONSOLE >> Executing command: %s\n", admin_buffer);
        int return_value = system(admin_buffer);
        return return_value;
    }
    else
    {
        // Error date and time format
        printf("CONSOLE >> Bad input date and time format !\n");
        return -1;
    }
}