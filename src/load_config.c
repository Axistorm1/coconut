/*
** EPITECH PROJECT, 2025
** coconut
** File description:
** load_config
*/

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "coconut.h"
#include "utils.h"

static bool update_default_arguments(
    char *key, char *value, arguments_t *arguments)
{
    if (strcmp(key, "default_sort") == 0) {
        arguments->sort_mask = sort_mask(value);
        if (arguments->sort_mask == -1)
            return false;
        return true;
    }
    if (strcmp(key, "default_lang") == 0) {
        arguments->language = strdup(value);
        return true;
    }
    if (strcmp(key, "default_style_checker") == 0) {
        arguments->style_checker = strdup(value);
        return true;
    }
    if (strcmp(key, "default_report_file") == 0) {
        arguments->report_file = strdup(value);
        return true;
    }
    return false;
}

// Expected config file format is default_opt=opt_value
static bool parse_default_arguments(
    arguments_t *arguments, char *line)
{
    char *key = NULL;
    char *value = NULL;

    if (line[0] == '#')
        return true;
    key = strtok(line, "=");
    value = strtok(NULL, "\n");
    if (key == NULL || value == NULL) {
        write(2, "Config file is not properly set up\n", 36);
        return false;
    }
    if (update_default_arguments(key, value, arguments) == false) {
        write(2, "Error reading config file\n", 27);
        return false;
    }
    return true;
}

// Need to add a check to see if all values are correct
// For now, let's trust the user
bool load_config(arguments_t *arguments)
{
    char *config_file = NULL;
    FILE *f_stream = NULL;
    char *line = NULL;
    size_t len = 0;

    config_file = get_config_file();
    f_stream = fopen(config_file, "r");
    if (is_file_stream_null(f_stream, "Config file not found\n"))
        return false;
    while (getline(&line, &len, f_stream) != -1)
        if (parse_default_arguments(arguments, line) == false)
            return false;
    if (line)
        free(line);
    free(config_file);
    fclose(f_stream);
    return true;
}
