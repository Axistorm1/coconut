#include <stdbool.h>
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

static char *get_file_extension(char *filepath)
{
    char *extension = &strrchr(filepath, '.')[1];

    if (extension[0] == '/')
        return NULL;
    return extension;
}

bool is_object_file(char *filepath)
{
    char *extension = get_file_extension(filepath);

    if (strstr(filepath, "Makefile") != NULL)
        return false;
    if (extension == NULL || strcmp(extension, "") == 0 ||
        strcmp(extension, "o") == 0 || strcmp(extension, "out") == 0 ||
        strcmp(extension, "a") == 0 || strcmp(extension, "gcno") == 0 ||
        strcmp(extension, "gcda") == 0)
        return true;
    return false;
}
