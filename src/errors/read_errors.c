/*
** EPITECH PROJECT, 2025
** coconut
** File description:
** read_errors
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "coconut.h"
#include "string_macros.h"
#include "utils.h"

static void add_errors(
    error_stats_t *error_stats, const error_content_t *error)
{
    int severity = 0;

    severity = error->severity;
    if (severity == FATAL)
        error_stats->fatals++;
    if (severity == MAJOR)
        error_stats->majors++;
    if (severity == MINOR)
        error_stats->minors++;
    if (severity == INFO)
        error_stats->infos++;
}

static bool check_ignored_files(
    const arguments_t *arguments,
    const error_content_t *error)
{
    if (!arguments->ignored_files || !arguments->ignored_files[0])
        return false;
    for (int i = 0; arguments->ignored_files[i]; i++) {
        if (strncmp(arguments->ignored_files[i], &error->filepath[2],
            strlen(arguments->ignored_files[i])) == 0) {
            return true;
        }
    }
    return false;
}

static void disassemble_error_line(char *line, error_content_t *content,
    const arguments_t *arguments)
{
    content->filepath = strdup(strtok(line, ":"));
    if (check_ignored_files(arguments, content) == false) {
        content->line = strdup(strtok(NULL, ":"));
        content->severity = error_severity(&strtok(NULL, ":")[1]);
        content->error_code = strndup(&strtok(NULL, ":")[2], 3);
        if (content->error_code[2] == '\n')
            content->error_code[2] = 0;
    } else {
        content->filepath = NULL;
    }
}

static error_content_t *read_report_lines(
    error_stats_t *stats, FILE *f_stream,
    const arguments_t *arguments)
{
    char *line = NULL;
    size_t len = 0;
    error_content_t *list = NULL;

    list = malloc(sizeof(error_content_t));
    if (!list)
        return NULL;
    while (getline(&line, &len, f_stream) != -1) {
        list = realloc(list, (size_t)(stats->total + 1) *
            sizeof(error_content_t));
        disassemble_error_line(line, &list[stats->total], arguments);
        if (list[stats->total].filepath != NULL) {
            add_errors(stats, &list[stats->total]);
            stats->total++;
        }
    }
    if (line)
        free(line);
    return list;
}

error_content_t *read_style_reports(
    error_stats_t *stats, const arguments_t *arguments)
{
    FILE *f_stream = NULL;
    error_content_t *list = NULL;

    f_stream = fopen(arguments->report_file, "r");
    if (is_file_stream_null(f_stream, REPORT_NOT_FOUND))
        return NULL;
    list = read_report_lines(stats, f_stream, arguments);
    if (list == NULL)
        return NULL;
    fclose(f_stream);
    return list;
}
