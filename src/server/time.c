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
    strftime(buffer, MAX_FORMATED_TIME_LENGTH, format, timeinfo);
    return buffer;
}

int set_time(char *time)
{
    struct tm tm;
    if (strptime(time, "%F %T", &tm) != NULL)
    {
        time_t t = mktime(&tm);

        // printf("year: %d; month: %d; day: %d;\n", tm.tm_year, tm.tm_mon, tm.tm_mday);
        // printf("hour: %d; minute: %d; second: %d\n",  tm.tm_hour, tm.tm_min, tm.tm_sec);
        // printf("week day: %d; year day: %d\n", tm.tm_wday, tm.tm_yday);

        char admin_buffer[ADMIN_BUFFER_LENGTH];
        sprintf(admin_buffer, "sudo ./admin_app %li", t);

        printf("CONSOLE >> Executing command: %s\n", admin_buffer);
        int return_value = system(admin_buffer);
        return return_value;
    }
    else
    {
        printf("CONSOLE >> Bad input date and time format !\n");
        return -1;
    }
}