#include <stdio.h>
#include <sys/time.h>

// IN DEV
int main() {
    struct timeval tv;

    tv.tv_sec = 1626349200;
    tv.tv_usec = 0;

    if (settimeofday(&tv, NULL) == -1)
        return 1;

    return 0;
}