#include "libmx.h"

int mx_bubble_sort(char **arr, int size) {
    int counter = 0;
    bool is_swapped;

    for (int i = 0; i < size - 1; i++) {
        is_swapped = false;

        for (int j = 0; j < size - i - 1; j++) {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
                char *bubble = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = bubble;
                is_swapped = true;
                counter++;
            }
        }

        if (!is_swapped) {
            break;
        }
    }

    return counter;
}

