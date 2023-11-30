#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    if (arr == NULL
        || s == NULL
        || size <= 0) {
        *count = 0;
        return -1;
    }

    int first = 0;
    int last = size - 1;

    while (first <= last) {
        int middle = (first + last) / 2;
        (*count)++;
        int comparison = mx_strcmp(arr[middle], s);

        if (comparison == 0) {
            return middle;
        }
        else if (comparison < 0) {
            first = middle + 1;
        }
        else {
            last = middle - 1;
        }
    }

    *count = 0;

    return -1;
}

