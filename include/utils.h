#ifndef COCONUT_UTILS_H_
    #define COCONUT_UTILS_H_

    #include <stdbool.h>
    #include <stdio.h>
    #include <sys/types.h>

int error_severity(const char *line);
bool is_object_file(const char *filepath);
ulong get_terminal_size(void);
char *get_config_file(void);
bool is_file_stream_null(const FILE *file_stream, const char *error_message);
long get_file_size(const char *filepath);

#endif /* COCONUT_UTILS_H_ */
