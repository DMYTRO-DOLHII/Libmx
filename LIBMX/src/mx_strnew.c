#include <libmx.h>

char *mx_strnew(const int size) {
    if (size < 0) {
        return NULL; 
    }
    char *newStr = (char *)malloc(size + 1);

    if (newStr != NULL) {
        for (int i = 0; i < size; i++) {
            newStr[i] = '\0';
        }
        newStr[size] = '\0';
    }

    return newStr;
}
