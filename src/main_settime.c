#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "core/security.h"

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        if (check_DEP() != 0)
        {
            exit(EXIT_FAILURE);
        }
        if (drop_privilegies() != 0)
        {
            exit(EXIT_FAILURE);
        }
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
        if (settimeofday(&tv, NULL) != 0)
            exit(EXIT_FAILURE);
    }

    return 0;
}
