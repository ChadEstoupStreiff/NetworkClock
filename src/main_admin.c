#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (setuid(0))
    {
        perror("Permission denied");
        exit(EXIT_FAILURE);
    }

    if (argc <= 1)
    {
        perror("No argument given");
        exit(EXIT_FAILURE);
    }

    long int new_time = atol(argv[1]);
    if (new_time <= 0)
    {
        perror("Invalid argument");
        exit(EXIT_FAILURE);
    }
    printf("New time: %li\n", new_time);

    struct timeval tv;
    tv.tv_sec = new_time;
    tv.tv_usec = 0;

    if (settimeofday(&tv, NULL) < 0)
    {
        perror("Can't set time");
        exit(EXIT_FAILURE);
    }

    return 0;
}