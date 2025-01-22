#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "coconut.h"

static void add_errors(error_stats_t *error_stats, error_content_t *error)
{
    int severity = error->severity;
    if (severity == 0)
        error_stats->fatals++;
    if (severity == 1)
        error_stats->majors++;
    if (severity == 2)
        error_stats->minors++;
    if (severity == 3)
        error_stats->infos++;
}

static void disassemble_error_line(char *line, error_content_t *content)
{
    content->filepath = strdup(strtok(line, ":"));
    content->line = strdup(strtok(NULL, ":"));
    content->severity = error_severity(strtok(NULL, ":"));
    content->error_code = strndup(&strtok(NULL, ":")[2], 2);
}

error_content_t *read_style_reports(error_stats_t *error_stats)
{
    FILE *f_stream = fopen(STYLE_REPORTS, "r");
    char *line = NULL;
    size_t len = 0;
    error_content_t *error_list = malloc(sizeof(error_content_t));

    if (f_stream == NULL) {
        write(2, "Couldn't read coding-style-reports.log\n", 40);
        free(error_list);
        return NULL;
    }
    while (getline(&line, &len, f_stream) != -1) {
        error_list = realloc(error_list, (error_stats->total + 1) * sizeof(error_content_t));
        disassemble_error_line(line, &error_list[error_stats->total]);
        add_errors(error_stats, &error_list[error_stats->total]);
        error_stats->total++;
    }
    if (line)
        free(line);
    fclose(f_stream);
    return error_list;
}
