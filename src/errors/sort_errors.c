/*
** EPITECH PROJECT, 2025
** coconut
** File description:
** sort_errors
*/

#include "coconut.h"
#include <stdlib.h>
#include <string.h>

static int severity_cmp(const void *error1, const void *error2)
{
    return ((error_content_t *)error1)->severity -
        ((error_content_t *)error2)->severity;
}

static int error_cmp(const void *error1, const void *error2)
{
    return strcmp(((error_content_t *)error1)->error_code,
        ((error_content_t *)error2)->error_code);
}

void sort_errors(error_content_t *error_list, int sort_mask, int error_count)
{
    int (*sort_functions[3])(const void *, const void *) =
        {NULL, &error_cmp, &severity_cmp};

    qsort(error_list,
        (size_t)error_count,
        sizeof(error_content_t),
        sort_functions[sort_mask]);
}
