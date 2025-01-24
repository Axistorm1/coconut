#include <unistd.h>
#include "coconut.h"

int display_usage(void)
{
    write(1,
        "Usage: coconut [option]\n"
        "  -c        Run coding-style-checker before displaying errors\n"
        "  -v        Display additional information\n"
        "  -r        Remove log file after displaying errors\n"
        "  -s [opt]  Sort output either by \"file\", \"error\" or "
        "\"severity\" (default \"file\")\n"
        "  -l        Add a line between different errors depending on "
        "the sorting flag\n", 341);
    return 1;
}
