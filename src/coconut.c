#include <stdio.h>
#include <unistd.h>
#include "../include/coconut.h"

int handle_arguments(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, "iwl")) != -1) {
        switch (opt) {
            case 'i':
                printf("Option -i was set\n");
                break;
            case 'w':
                printf("Option -w was set\n");
                break;
            case 'l':
                printf("Option -l was set\n");
                break;
            default:
                fprintf(stderr, "Usage: %s [-iwl]\n", argv[0]);
                return 1;
        }
    }
    return 0;
}

int handle_args(int argc, char **argv, arguments_t arguments)
{
    int opt = 0;
    while (opt != -1) {
        opt = getopt(argc, argv, "hcrs:f:v");
        if (opt == '?')
            write(2, "Incorrect argument\n", 20);
    }
}

int main(int argc, char **argv)
{

}
