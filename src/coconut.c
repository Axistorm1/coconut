#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "coconut.h"

static int sort_mask(char *optarg)
{
    if (strcmp(optarg, "file") == 0)
        return 1;
    if (strcmp(optarg, "error") == 0)
        return 2;
    if (strcmp(optarg, "severity") == 0)
        return 4;
    return 0;
}

static int handle_args(int argc, char **argv, arguments_t *arguments)
{
    int opt = 0;

    while (opt != -1) {
        opt = getopt(argc, argv, "hcrs:f:v");
        if (opt == '?')
            return -1;
        if (opt == 'h')
            return display_usage();
        if (opt == 'c')
            arguments->run_coding_style = true;
        if (opt == 'r')
            arguments->remove_log_file = true;
        if (opt == 's' && optarg != NULL)
            arguments->sort_mask = sort_mask(optarg);
        if (opt == 'f' && optarg != NULL)
            arguments->file = optarg;
        if (opt == 'v')
            arguments->verbose = true;
    }
    return 0;
}

static void free_content(error_content_t *errors, int total_errors)
{
    for (int i = 0; i < total_errors; i++) {
        free((&errors[i])->error_code);
        free((&errors[i])->filepath);
        free((&errors[i])->line);
    }
    free(errors);
}

int main(int argc, char **argv)
{
    arguments_t arguments = {0};
    error_stats_t error_stats = {0};
    error_content_t *errors = NULL;

    handle_args(argc, argv, &arguments);
    if (arguments.run_coding_style == true)
        system("coding-style . .");
    errors = read_style_reports(&error_stats);
    if (errors == NULL)
        return -1;
    write_top_line();
    write_errors(errors, &error_stats, arguments.verbose);
    if (error_stats.total == 0)
        write(1, "No error found\n", 16);
    else
        write_bottom_line(&error_stats);
    free_content(errors, error_stats.total);
}
