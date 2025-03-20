/*
** EPITECH PROJECT, 2025
** coconut
** File description:
** display_additional
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "coconut.h"
#include "utils.h"

static char *dash_line_buffer(unsigned long size)
{
    char *buffer = NULL;

    buffer = malloc(sizeof(char) * (size + 1));
    if (!buffer)
        return NULL;
    buffer[size] = 0;
    memset(buffer, '-', size);
    return buffer;
}

void write_top_line(char *reports_file)
{
    char *buffer = NULL;

    buffer = dash_line_buffer(get_terminal_size());
    if (!buffer)
        return;
    printf("%s\n"
        "        │ File: %s\n"
        "%s\n",
        buffer, reports_file, buffer);
    free(buffer);
}

void write_bottom_line(error_stats_t *stats)
{
    char *buffer = NULL;

    buffer = dash_line_buffer(get_terminal_size());
    if (!buffer)
        return;
    printf("%s\n"
        "        │ Total: %d | Fatal: %d | Major: %d | Minor: %d | Info: %d\n"
        "%s\n",
        buffer, stats->total, stats->fatals, stats->majors,
        stats->minors, stats->infos, buffer);
    free(buffer);
}

void write_no_error(void)
{
    char *buffer = NULL;

    buffer = dash_line_buffer(get_terminal_size());
    if (!buffer)
        return;
    printf("%s\n"
        "        │ No error found! Great job\n"
        "%s\n",
        buffer, buffer);
    free(buffer);
}
