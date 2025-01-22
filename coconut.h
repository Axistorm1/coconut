#ifndef COCONUT_H_
    #define COCONUT_H_

    #include <stddef.h>
    #include <stdint.h>

    #define STYLE_REPORTS "coding-style-reports.log"

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

// write_report.c
void disassemble_error_line(char *line, size_t error_nb);
void write_top_line();
void write_bottom_line(size_t fatals, size_t majors, size_t minors, size_t infos);

// utils.c
uint8_t error_severity(char *line);
uint8_t get_terminal_size();

#endif /* COCONUT_H_ */
