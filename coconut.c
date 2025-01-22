#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "coconut.h"

static void read_style_reports(void)
{
    FILE *f_stream = fopen(STYLE_REPORTS, "r");
    char *line = NULL;
    ssize_t read = 0;
    size_t len = 0;
    size_t error_count = 1;

    if (f_stream == NULL) {
        write(2, "Couldn't read coding-style-reports.log\n", 40);
        return;
    }
    write_top_line();
    read = getline(&line, &len, f_stream);
    while (read != -1) {
        disassemble_error_line(line, error_count);
        error_count++;
        read = getline(&line, &len, f_stream);
    }
    if (line)
        free(line);
    write_bottom_line(error_count - 1, 0, 0, 0);
    fclose(f_stream);
}

int main(int argc, char **argv)
{
    system("coding-style . .");
    read_style_reports();
}
