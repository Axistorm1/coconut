#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "coconut.h"
#include "string_macros.h"

static int sort_mask(char *optarg)
{
    if (strcmp(optarg, "file") == 0)
        return 0;
    if (strcmp(optarg, "error") == 0)
        return 1;
    if (strcmp(optarg, "severity") == 0)
        return 2;
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

static bool handle_flags(int opt, arguments_t *arguments)
{
    if (opt == '?')
        return false;
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

static int handle_args(int argc, char **argv, arguments_t *arguments)
{
    int opt = 0;

    while (opt != -1) {
        opt = getopt(argc, argv, HANDLED_FLAGS);
        if (opt == 'h')
            return display_usage();
        if (handle_flags(opt, arguments) == false)
            return -1;
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
    error_content_t *errors, error_stats_t *error_stats,
    arguments_t *arguments)
{
    if (arguments->sort_mask != 0)
        sort_errors(errors, arguments->sort_mask, error_stats->total);
    write_top_line();
    write_errors(errors, error_stats, arguments);
    if (error_stats->total == 0)
        return write_no_error();
    write_bottom_line(error_stats);
}

static void run_coding_style(bool run_coding_style)
{
    int system_return = 0;

    if (run_coding_style)
        system_return = system(RUN_CODING_STYLE_COMMAND);
    if (system_return == -1 || system_return == 127)
        write(1, "Error running coding style checker\n", 36);
}

static void remove_log_file(bool remove_log_file)
{
    int system_return = 0;

    if (remove_log_file)
        system_return = system(REMOVE_LOG_REPORT);
    if (system_return == -1 || system_return == 127)
        write(1, "Error removing log file\n", 25);
}

int main(int argc, char **argv)
{
    arguments_t arguments = {0};
    error_stats_t error_stats = {0};
    error_content_t *errors = NULL;
    int handling_result = 0;

    handling_result = handle_args(argc, argv, &arguments);
    if (handling_result == -1)
        return -1;
    if (handling_result == 1)
        return 0;
    run_coding_style(arguments.run_coding_style);
    errors = read_style_reports(&error_stats);
    if (errors == NULL)
        return -1;
    write_report(errors, &error_stats, &arguments);
    free_content(errors, error_stats.total);
    remove_log_file(arguments.remove_log_file);
}
