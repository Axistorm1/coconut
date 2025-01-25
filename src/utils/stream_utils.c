#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

bool is_file_stream_null(FILE *file_stream, char *error_message)
{
    if (file_stream == NULL) {
        write(1, error_message, strlen(error_message));
        return true;
    }
    return false;
}
