#include <stdio.h>
#include "time.h"

void start_console() {
    while(1) {
        int buffer_length = 1024;
        char buffer[buffer_length];

        printf("CONSOLE>> Enter command:\n");
        scanf("%1023s", buffer);

        for (int i = 0; i < 20; i++) {
            printf("%c\n", buffer[i]);
        }

        printf("CONSOLE>> Time: %s\n", get_time(buffer));
    }
}