#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "coconut.h"

static char *dash_line_buffer(int size)
{
    char *buffer = malloc(sizeof(char) * (size + 1));

    buffer[size] = 0;
    memset(buffer, '-', size);
    return buffer;
}

void write_top_line(void)
{
    char *buffer = dash_line_buffer(get_terminal_size());

    printf("%s\n"
        "        │ File: %s\n"
        "%s\n", buffer, STYLE_REPORTS, buffer);
    free(buffer);
}

void write_bottom_line(error_stats_t *stats)
{
    char *buffer = dash_line_buffer(get_terminal_size());

    printf("%s\n"
        "        │ Total: %d | Fatal: %d | Major: %d | Minor: %d | Info: %d\n"
        "%s\n", buffer, stats->total, stats->fatals, stats->majors,
        stats->minors, stats->infos, buffer);
    free(buffer);
}

void write_no_error(void)
{
    char *buffer = dash_line_buffer(get_terminal_size());

    printf("%s\n"
        "        │ No error found! Great job\n"
        "%s\n", buffer, buffer);
    free(buffer);
}
