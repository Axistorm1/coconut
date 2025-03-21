#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "coconut.h"
#include "string_macros.h"

int sort_mask(char *mask_str)
{
    if (strcmp(mask_str, "file") == 0)
        return SORT_FILE;
    if (strcmp(mask_str, "error") == 0)
        return SORT_ERROR;
    if (strcmp(mask_str, "severity") == 0)
        return SORT_SEVERITY;
    return -1;
}

static bool is_sort_flag_correct(int sort_mask)
{
    if (sort_mask == -1) {
        write(2, "Incorrect sorting type\n", 24);
        return false;
    }
    return true;
}

static char **parse_ignored_dir(char **ignored_dirs, arguments_t *arguments)
{
    int i = 0;

    if (!ignored_dirs || !ignored_dirs[0]) {
        fprintf(stderr, "No directories specified. Skip option\n");
        return NULL;
    }
    arguments->ignored_files = malloc(sizeof(char *));
    for (i = 0; ignored_dirs[i]; i++) {
        arguments->ignored_files = realloc(arguments->ignored_files,
            sizeof(char *) * (size_t)i + 2);
        arguments->ignored_files[i] = strdup(ignored_dirs[i]);
        if (!arguments->ignored_files[i]) {
            fprintf(stderr, "Error allocating memory for ignored_files\n");
        }
    }
    arguments->ignored_files[i] = NULL;
    return arguments->ignored_files;
}

static bool handle_flags(int opt, arguments_t *arguments,
    char **av)
{
    if (opt == 'e')
        arguments->ignored_files = parse_ignored_dir(av, arguments);
    if (opt == 'c')
        arguments->run_coding_style = true;
    if (opt == 'r')
        arguments->remove_log_file = true;
    if (opt == 's' && optarg != NULL) {
        arguments->sort_mask = sort_mask(optarg);
        if (!is_sort_flag_correct(arguments->sort_mask))
            return false;
    }
    if (opt == 'f' && optarg != NULL)
        arguments->file = optarg;
    if (opt == 'v')
        arguments->verbose = true;
    if (opt == 'l')
        arguments->add_spaces = true;
    return true;
}

int handle_args(int argc, char **argv, arguments_t *arguments)
{
    int opt = 0;
    int i = 1;

    while (opt != -1) {
        opt = getopt(argc, argv, HANDLED_FLAGS);
        if (opt == 'h')
            return display_usage();
        if (handle_flags(opt, arguments, &argv[i + 1]) == false)
            return -1;
        i++;
    }
    return 0;
}
