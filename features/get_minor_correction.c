#include "../include/coconut.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int open_and_print_line(error_line_content_t *line)
{
    FILE *file = fopen(line->filepath, "r");
    char *code_line = NULL;
    size_t len = 0;
    __ssize_t read;

    if (file == NULL) {
        return 84;
    }
    read = getline(&code_line, &len, file);
    for (int i = 1; i < line->line && read != -1; i++) {
        read = getline(&code_line, &len, file);
    }
    printf("line = %s\n", code_line);
    fclose(file);
    free(line);
    return 0;
}

int error_severity(char *line)
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
