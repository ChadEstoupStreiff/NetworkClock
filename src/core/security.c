#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int check_DEP()
{
    // Read CPU info
    FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
    char *arg = 0;
    size_t size = 0;

    // Search nx tag
    while (getdelim(&arg, &size, 0, cpuinfo) != -1)
    {
        if (strstr(arg, " nx ") != NULL)
        {
            fclose(cpuinfo);
            return 1;
        }
    }
    return 0;
}

int drop_root_privilegies()
{
    uid_t uid = getuid();
    gid_t gid = getgid();

    if ((setgid(gid) != 0) || (setuid(uid) != 0))
        return 0;

    return 1;
}