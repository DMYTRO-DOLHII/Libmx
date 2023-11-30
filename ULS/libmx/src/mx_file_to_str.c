#include "libmx.h"

char *mx_file_to_str(const char *file) {
    if (file == NULL) {
        return NULL;
    }

    int file_descr = open(file, O_RDONLY);

    if (file_descr == -1) {
        return NULL;
    }

    int size = 0;
    int byte_count;
    char c;

    while((byte_count = read(file_descr, &c, 1)) != 0) {
        if (byte_count == -1) {
            return NULL;
        }

        size++;
    }

    if (size == 0) {
        return NULL;
    }

    if (close(file_descr) == -1) {
        return NULL;
    }

    file_descr = open(file, O_RDONLY);

    if (file_descr == -1) {
        return NULL;
    }

    char *str = mx_strnew(size);
    int i = 0;

    while ((byte_count = read(file_descr, &c, 1)) != 0) {
        if (byte_count == -1) {
            return NULL;
        }

        str[i] = c;
        i++;
    }

    if (close(file_descr) == -1) {
        return NULL;
    }

    str[i] = '\0';

    return str;
}

