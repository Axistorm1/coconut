#ifndef COCONUT_H_
    #define COCONUT_H_

    #include <stdbool.h>

typedef struct arguments_s {
    char **files;
    unsigned int sort_mask;
    bool remove_log_file;
    bool verbose;
    bool run_coding_style;
} arguments_t;

typedef struct error_line_content_s {
    int line;
    int severity;
    char *filepath;
    char *error_code;
} error_line_content_t;

#endif /* COCONUT_H_ */
