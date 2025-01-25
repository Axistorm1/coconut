#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "coconut.h"
#include "string_macros.h"
#include "utils.h"

static void add_errors(error_stats_t *error_stats, error_content_t *error)
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

static void disassemble_error_line(char *line, error_content_t *content)
{
    content->filepath = strdup(strtok(line, ":"));
    content->line = strdup(strtok(NULL, ":"));
    content->severity = error_severity(&strtok(NULL, ":")[1]);
    content->error_code = strndup(&strtok(NULL, ":")[2], 3);
    if (content->error_code[2] == '\n')
        content->error_code[2] = 0;
}

error_content_t *read_style_reports(error_stats_t *stats, char *reports_file)
{
    FILE *f_stream = NULL;
    char *line = NULL;
    size_t len = 0;
    error_content_t *list = NULL;

    f_stream = fopen(reports_file, "r");
    if (is_file_stream_null(f_stream, REPORT_NOT_FOUND))
        return NULL;
    list = malloc(sizeof(error_content_t));
    while (getline(&line, &len, f_stream) != -1) {
        list = realloc(list, (stats->total + 1) * sizeof(error_content_t));
        disassemble_error_line(line, &list[stats->total]);
        add_errors(stats, &list[stats->total]);
        stats->total++;
    }
    if (line)
        free(line);
    fclose(f_stream);
    return list;
}
