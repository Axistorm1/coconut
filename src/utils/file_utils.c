#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>

static char *get_file_extension(char *filepath)
{
    char *extension = NULL;
    char *filename = NULL;

    filename = strrchr(filepath, '/');
    if (filename == NULL)
        return NULL;
    filename = &filename[1];
    extension = strrchr(filename, '.');
    if (extension == NULL)
        return NULL;
    return &extension[1];
}

bool is_object_file(char *filepath)
{
    char *extension = NULL;

    extension = get_file_extension(filepath);
    if (strstr(filepath, "Makefile") != NULL)
        return false;
    if (extension == NULL || strcmp(extension, "") == 0 ||
        strcmp(extension, "o") == 0 || strcmp(extension, "out") == 0 ||
        strcmp(extension, "a") == 0 || strcmp(extension, "gcno") == 0 ||
        strcmp(extension, "gcda") == 0)
        return true;
    return false;
}

char *get_config_file(void)
{
    char *config_file = NULL;
    char *home_dir = NULL;

    config_file = calloc(256, sizeof(char *));
    memset(config_file, 0, 256);
    home_dir = getenv("HOME");
    strcat(config_file, home_dir);
    strcat(config_file, "/.config/coconut/coconut.conf");
    return config_file;
}

long get_file_size(char *filepath)
{
    struct stat stats = {};

    stat(filepath, &stats);
    return stats.st_size;
}
