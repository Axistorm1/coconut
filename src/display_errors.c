#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "coconut.h"

// Fatal black
// Major red
// Minor yellow
// Info cyan
static const char *colors[4] = {
    "\x1b[30m\x1b[2m",
    "\x1b[31m",
    "\x1b[33m",
    "\x1b[36m"};

static void write_verbose(error_content_t *error)
{
    FILE *file = fopen(error->filepath, "r");
    char *line = NULL;
    size_t len = 0;
    int line_nb = atoi(error->line);

    if (is_object_file(error->filepath) == true) {
        fclose(file);
        return;
    }
    if (file == NULL){
        write(2, "Error opening file\n", 20);
        return;
    }
    for (int i = 0; i < line_nb && getline(&line, &len, file) != -1; i++);
    line[strlen(line) - 1] = 0;
    printf("        │ -> %.50s\n", line);
    fclose(file);
    free(line);
}

static void write_formatted_error(error_content_t *error, int error_nb)
{
    char *error_message = get_error_message(error->error_code);
    const char *color_code = colors[error->severity];

    printf("%5d   │ %s%-21.21s -> (l-%s)%.*s %4s \x1b[0m│ %s\n", error_nb,
        color_code, error->filepath, error->line, 5 - (int)strlen(error->line),
        "     ", error->error_code, &error_message[4]);
}

void write_errors(
    error_content_t *errors, error_stats_t *error_stats, bool verbose)
{
    for (int i = 0; i < error_stats->total; i++) {
        write_formatted_error(&errors[i], i + 1);
        if (verbose)
            write_verbose(&errors[i]);
    }
}
