#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "coconut.h"

static const char *c_error_messages[42] = {
    "O1: Object file",
    "O2: Extension should be .c or .h",
    "O3: Max functions reached (10)",
    "O4: File name must be snake_case",
    "G1: Missing header",
    "G2: Separate functions with a single line",
    "G3: Preprocessor directive indentation",
    "G4: Only global constants",
    "G5: Can only include .h files",
    "G6: Missing line ending",
    "G7: Trailing spaces",
    "G8: Leading/Trailing lines",
    "G9: Define constant values",
    "G10:Inline assembly is forbidden",
    "F1: Functions should do a single thing",
    "F2: Functions names must be snake_case",
    "F3: Max columns reached (80)",
    "F4: Max lines reached (20)",
    "F5: Max function parameters reached (4)",
    "F6: Functions without parameters take void",
    "F7: Always pass structures as pointers",
    "F8: No comments within a function",
    "F9: No nested functions",
    "L1: Only one statement per line",
    "L2: 4 spaces per indentation",
    "L3: One single space when used as separator",
    "L4: Curly brackets wrongly placed",
    "L5: One variable per statement at the function's top",
    "L6: Blank line between variables and body",
    "V1: Defines in caps, typedefs with _t",
    "V2: Structures must be coherent",
    "V3: '*' attached to the variable",
    "C1: No more than 3 conditional branches",
    "C2: Ternary operators must be kept simple",
    "C3: goto keyword is forbidden",
    "H1: Incorrect header content",
    "H2: Missing header guard",
    "H3: One line and statement per macro",
    "A1: Not modified variables must be marked as constant",
    "A2: Use accurate types",
    "A3: Missing line break at the end of file",
    "A4: Intern-only functions and global variables as static"};

static const char *h_error_messages[15] = {
    "O1: Object file",
    "O2: Extension should be .hs",
    "O3: Badly organized project",
    "O4: File name must be UpperCamelCase",
    "E1: Language extensions are forbidden",
    "T1: Missing type signature",
    "M1: Mutable variables are forbidden",
    "F1: Functions must be less than 10 lines and 80 columns",
    "F2: Function name must be lowerCamelCase",
    "V1: Variable name must be lowerCamelCase",
    "C1: No nested if statements",
    "C2: Guards must be expressed as such",
    "D1: Unjustified use of the do notation is forbidden",
    "D2: Useless generators are forbidden"
    "P1: File could not be parsed"
};

char *get_error_message(const char *error_code)
{
    char *message = NULL;

    printf("Error code: %s\n", error_code);
    for (int i = 0; i < 42; i++) {
        if (error_code[0] == 'H')
            message = strstr(h_error_messages[i], &error_code[2]);
        if (!message)
            message = strstr(c_error_messages[i], &error_code[2]);
        if (message)
            return message;
    }
    return message;
}
