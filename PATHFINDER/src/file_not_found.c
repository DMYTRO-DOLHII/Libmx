#include "../inc/pathfinder.h"

void file_not_found(const char *filename) {
    int file = open(filename, O_RDONLY);

    if (file == -1) {
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" does not exist\n"); 
        exit(1);
    }

    close(file);
}
