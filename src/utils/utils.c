#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "coconut.h"

int error_severity(char *line)
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

int get_terminal_size(void)
{
    struct winsize size = {0};

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
        perror("ioctl");
        return 0;
    }
    return size.ws_col;
}
