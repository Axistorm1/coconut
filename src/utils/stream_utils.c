#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"

bool is_file_stream_null(const FILE *file_stream, const char *error_message)
{
    if (file_stream == NULL) {
        write(1, error_message, strlen(error_message));
        return true;
    }
    return false;
}
