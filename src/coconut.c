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

static void write_report(
    error_content_t *errors, error_stats_t *error_stats, bool verbose)
{
    write_top_line();
    write_errors(errors, error_stats, verbose);
    if (error_stats->total == 0)
        write_no_error();
    else
        write_bottom_line(error_stats);
}

int main(int argc, char **argv)
{
    arguments_t arguments = {0};
    error_stats_t error_stats = {0};
    error_content_t *errors = NULL;
    int handling_result = handle_args(argc, argv, &arguments);

    if (handling_result == -1)
        return -1;
    if (handling_result == 1)
        return 0;
    if (arguments.run_coding_style == true)
        system("coding-style . .");
    errors = read_style_reports(&error_stats);
    if (errors == NULL)
        return -1;
    write_report(errors, &error_stats, arguments.verbose);
    free_content(errors, error_stats.total);
    if (arguments.remove_log_file == true)
        system("rm -f coding-style-reports.log");
}
