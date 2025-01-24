#ifndef COCONUT_H_
    #define COCONUT_H_

    #include <stdbool.h>

    #define STYLE_REPORTS "coding-style-reports.log"

typedef struct arguments_s {
    char *file;
    int sort_mask;
    bool remove_log_file;
    bool verbose;
    bool run_coding_style;
    bool add_spaces;
} arguments_t;

typedef struct error_content_s {
    char *line;
    int severity;
    char *filepath;
    char *error_code;
} error_content_t;

typedef struct error_stats_s {
    int fatals;
    int majors;
    int minors;
    int infos;
    int total;
} error_stats_t;

enum error_severities {
    FATAL,
    MAJOR,
    MINOR,
    INFO
};

enum error_codes {
    O1, O2, O3, O4,
    G1, G2, G3, G4, G5, G6, G7, G8, G9, G10,
    F1, F2, F3, F4, F5, F6, F7, F8, F9,
    L1, L2, L3, L4, L5, L6,
    V1, V2, V3,
    C1, C2, C3,
    H1, H2, H3,
    A1, A2, A3, A4
};

int display_usage(void);
error_content_t *read_style_reports(error_stats_t *error_stats);
int error_severity(char *line);
char *get_error_message(char *error_code);
void write_errors(
    error_content_t *errors, error_stats_t *stats, arguments_t *arguments);
bool is_object_file(char *filepath);
int get_terminal_size(void);
void write_top_line(void);
void write_bottom_line(error_stats_t *error_stats);
void write_no_error(void);
void sort_errors(error_content_t *error_list, int sort_mask, int error_count);

#endif /* COCONUT_H_ */
