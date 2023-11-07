#include "../inc/pathfinder.h"

void empty_file(const char *filename) {
    int file = open(filename, O_RDONLY);

    char strfer[1];
    size_t bytes_read = read(file, strfer, sizeof(strfer));

    if (bytes_read <= 0) {
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" is empty\n");
        exit(1);
    }

    close(file); 
}
