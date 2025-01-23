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
    if (sort_mask == 2)
        qsort(error_list, error_count, sizeof(error_content_t), &error_cmp);
    if (sort_mask == 4)
        qsort(error_list, error_count, sizeof(error_content_t), &severity_cmp);
}
