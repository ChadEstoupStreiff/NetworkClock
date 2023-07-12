#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_FORMATED_TIME_LENGTH 64

// function that take a format and return current time in this format
char* get_time(char* format)
{
    // Get time info
    time_t rawtime = time(NULL);
    struct tm *timeinfo = localtime(&rawtime);

    // Create buffer
    char* buffer = malloc(sizeof(char) * MAX_FORMATED_TIME_LENGTH);

    // Format time info into buffer
    strftime(buffer, MAX_FORMATED_TIME_LENGTH, format, timeinfo);
    return buffer;
}

char* set_time(int time)
{

}