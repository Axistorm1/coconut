#include <stdint.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "coconut.h"

int error_severity(char *line)
{
    line = &line[1];
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
    struct winsize size;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
        perror("ioctl");
        return 1;
    }
    return size.ws_col;
}

char *get_file_extension(char *filepath)
{
    char *return_value = NULL;
    unsigned long extension_pos = strcspn(&filepath[1], ".") + 2;

    if (extension_pos > strlen(filepath))
        return NULL;
    return_value = &filepath[extension_pos];
    return return_value;
}
