#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc == 0)
    {
        perror("No argument given");
        exit(1);
    }
    if (setuid(0))
    {
        perror("Permission denied");
        exit(1);
    }

    struct timeval tv;

    tv.tv_sec = atoi(argv[1]);
    tv.tv_usec = 0;

    if (settimeofday(&tv, NULL) == -1)
    {
        perror("Can't set time");
        exit(1);
    }

    return 0;
}