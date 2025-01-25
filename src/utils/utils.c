#include <sys/ioctl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "coconut.h"
#include "utils.h"

int error_severity(const char *line)
{
    if (strcmp(line, "FATAL") == 0)
        return FATAL;
    if (strcmp(line, "MAJOR") == 0)
        return MAJOR;
    if (strcmp(line, "MINOR") == 0)
        return MINOR;
    if (strcmp(line, "INFO") == 0)
        return INFO;
    return 3;
}

ulong get_terminal_size(void)
{
    struct winsize size = {0};

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
        perror("ioctl");
        return 0;
    }
    return (ulong)size.ws_col;
}
