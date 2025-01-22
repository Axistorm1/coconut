#include <string.h>
#include <unistd.h>
#include "../include/coconut.h"

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
            display_usage();
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

int main(int argc, char **argv)
{
    arguments_t arguments = {0};
    handle_args(argc, argv, &arguments);
}
