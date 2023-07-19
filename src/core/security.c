#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <linux/capability.h>
#include <sys/capability.h>

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
            return 0;
        }
    }
    return 1;
}

int drop_privilegies()
{
    uid_t uid = getuid();
    gid_t gid = getgid();

    if ((setgid(gid) != 0) || (setuid(uid) != 0))
        return 0;
    
    if (prctl(PR_CAPBSET_DROP, CAP_LAST_CAP, 0, 0, 0) == -1) {
        return 1;
    }

    if (prctl(PR_CAPBSET_READ, CAP_LAST_CAP) == -1) {
        return 1;
    }

    return 0;
}

int enable_settime_capability()
{
    cap_t caps = cap_get_proc();
    cap_value_t cap_value = CAP_SYS_TIME;
    if (cap_set_flag(caps, CAP_EFFECTIVE, 1, &cap_value, CAP_SET) == -1) {
        perror("cap_set_flag");
        return 1;
    }
    if (cap_set_proc(caps) == -1) {
        perror("cap_set_proc");
        return 1;
    }

    cap_t caps_enabled = cap_get_proc();
    if (caps_enabled == NULL) {
        perror("cap_get_proc");
        return 1;
    }
    if (cap_get_flag(caps_enabled, CAP_EFFECTIVE, 1, &cap_value) == -1) {
        perror("cap_get_flag");
        return 1;
    }

    cap_free(caps);
    cap_free(caps_enabled);

    return 0;
}