#include <stddef.h>
#include <string.h>
#include "coconut.h"

static const char *error_messages[42] = {
    "O1: Object file", "O2: Extension should be .c or .h", "O3: Max functions reached (10)", "O4: File name must be snake_case",
    "G1: Missing header", "G2: Separate functions with a single line", "G3: Preprocessor directive indentation", "G4: Only global constants", "G5: Can only include .h", "G6: Missing line ending", "G7: Trailing spaces", "G8: Leading/Trailing lines", "G9: Define constant values", "G10: Inline assembly is forbidden",
    "F1: Functions do a single thing", "F2: Functions names must be snake_case", "F3: Max columns reached (80)", "F4: Max lines reached (19)", "F5: Max function parameters reached (4)", "F6: Functions without parameter take void", "F7: Always pass structures as pointers", "F8: No comments within a function", "F9: No nested functions",
    "L1: Only one statement per line", "L2: 4 spaces per indentation", "L3: One single space when used as separator", "L4: Curly brackets wrongly placed", "L5: One variable per statement at the function's top", "L6: Blank line between variables and body",
    "V1: Defines in caps, typedefs with _t", "V2: Structures must be coherent", "V3: '*' attached to the variable",
    "C1: No more than 3 conditional branches", "C2: Ternary operators must be kept simple", "C3: goto keyword is forbidden",
    "H1: Incorrect header content", "H2: Missing header guard", "H3: One line and statement per macro",
    "A1: Not modified variables must be marked as constant", "A2: Use accurate types", "A3: Missing line break at the end of file", "A4: Mark intern-only functions and global variabels as static"};

char *get_error_message(char *error_code)
{
    char *tmp = NULL;

    for (int i = 0; i < 42; i++) {
        tmp = strstr(error_messages[i], error_code);
        if (tmp != NULL)
            return tmp;
    }
    return NULL;
}
