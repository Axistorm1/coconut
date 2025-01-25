#ifndef STRING_MACROS_H_
    #define STRING_MACROS_H_

    #define STYLE_REPORTS "coding-style-reports.log"
    #define ERROR_STR "%5d   │ %s%-32.32s -> (l-%s)%.*s %4s \x1b[0m│ %s\n"
    #define HANDLED_FLAGS "hcrs:f:vl"
    #define RUN_CODING_STYLE_COMMAND "coding-style . ."
    #define REMOVE_LOG_REPORT "rm -f coding-style-reports.log"
    #define REPORT_NOT_FOUND "Couldn't read coding-style-reports.log\n"

#endif /* STRING_MACROS_H_ */
