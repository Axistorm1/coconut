#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "coconut.h"
#include "string_macros.h"
#include "utils.h"

// Fatal black
// Major red
// Minor yellow
// Info cyan
static const char *colors[4] = {
    "\x1b[30m\x1b[2m",
    "\x1b[31m",
    "\x1b[33m",
    "\x1b[36m"};

static void write_verbose(const error_content_t *error)
{
    FILE *file = NULL;
    char *line = NULL;
    size_t len = 0;
    int line_nb = 0;
    struct stat stat_buffer;

    if (is_object_file(error->filepath) == true)
        return;
    if (stat(error->filepath, &stat_buffer) == -1 || stat_buffer.st_size == 0)
        return;
    file = fopen(error->filepath, "r");
    if (is_file_stream_null(file, "Error opening file\n"))
        return;
    line_nb = atoi(error->line);
    for (int i = 0; i < line_nb && getline(&line, &len, file) != -1; i++);
    line[strlen(line) - 1] = 0;
    printf("        │ -> %.120s\n", line);
    if (line)
        free(line);
    fclose(file);
}

static void write_formatted_error(
    const error_content_t *error,
    int error_nb,
    size_t term_size)
{
    char *error_message = NULL;
    const char *color_code = NULL;
    char file_and_line[term_size];
    int max_message_size = (int)(term_size - MAX_ERROR_SIZE - MAX_NB_SIZE);

    error_message = get_error_message(error->error_code);
    memset(file_and_line, 0, term_size);
    strncat(file_and_line, error->filepath, (size_t)max_message_size);
    strcat(file_and_line, ":");
    strcat(file_and_line, error->line);
    color_code = colors[error->severity];
    printf(ERROR_STR, error_nb, color_code, max_message_size, max_message_size,
        file_and_line, error->error_code, &error_message[4]);
}

static bool add_space_between_errors(
    int sort_mask, const error_content_t *error, const error_content_t *prev)
{
    if (sort_mask == SORT_FILE &&
        strcmp(error->filepath, prev->filepath) != 0)
        return true;
    if (sort_mask == SORT_ERROR &&
        strcmp(error->error_code, prev->error_code) != 0)
        return true;
    if (sort_mask == SORT_SEVERITY &&
        error->severity != prev->severity)
        return true;
    return false;
}

void write_errors(
    const error_content_t *errors,
    const error_stats_t *stats,
    const arguments_t *arguments)
{
    size_t term_size = get_terminal_size();

    if (term_size < 52) {
        write(STDERR_FILENO, "Terminal size is too small\n", 27);
        return;
    }
    for (int i = 0; i < stats->total; i++) {
        if (arguments->add_spaces && i != 0 &&
            add_space_between_errors(
                arguments->sort_mask, &errors[i], &errors[i - 1]))
            write(1, "\n", 1);
        write_formatted_error(&errors[i], i + 1, term_size);
        if (arguments->verbose)
            write_verbose(&errors[i]);
    }
}
