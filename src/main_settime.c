#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "core/security.h"

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        check_DEP();
        drop_privilegies();
        enable_settime_capability();

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
