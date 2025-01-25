#include <stdbool.h>
#include <string.h>
#include <unistd.h>
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

int handle_args(int argc, char **argv, arguments_t *arguments)
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
