#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    // Try to execute as root
    if (setuid(0))
    {
        perror("Permission denied");
        exit(EXIT_FAILURE);
    }

    // Test if argument is given
    if (argc <= 1)
    {
        perror("No argument given");
        exit(EXIT_FAILURE);
    }

    // Convert argument to long int
    long int new_time = atol(argv[1]);
    if (new_time <= 0)
    {
        perror("Invalid argument");
        exit(EXIT_FAILURE);
    }

    // Prepare variables to set time
    struct timeval tv;
    tv.tv_sec = new_time;
    tv.tv_usec = 0;

    // Set time
    if (settimeofday(&tv, NULL) < 0)
    {
        perror("Can't set time");
        exit(EXIT_FAILURE);
    }

    return 0;
}