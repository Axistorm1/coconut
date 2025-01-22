#include <stdint.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "coconut.h"

uint8_t error_severity(char *line)
{
    if (strstr(line, "FATAL"))
        return FATAL;
    if (strstr(line, "MAJOR"))
        return MAJOR;
    if (strstr(line, "MINOR"))
        return MINOR;
    if (strstr(line, "INFO"))
        return INFO;
    return 3;
}

uint8_t get_terminal_size()
{
    struct winsize size;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
        perror("ioctl");
        return 1;
    }
    return size.ws_col;
}
