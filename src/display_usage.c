#include <unistd.h>
#include "coconut.h"

int display_usage(void)
{
    write(1, "Usage: coconut [option]\n"
        " -c    Run coding-style-checker before displaying errors\n"
        " -v    Display additional information\n"
        " -r    Remove log file after displaying errors\n", 167);
    return 1;
}
