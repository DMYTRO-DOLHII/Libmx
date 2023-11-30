#include "libmx.h"

int mx_count_words(const char *str, char c) {
    if (str == NULL) {
        return -1;
    }

    int word_counter = 0;
    int i = 0;

    if (str[i] != '\0'
        && str[i] != c) {
        word_counter++;
        i++;
    }

    while (str[i] != '\0') {
        if (str[i] == c) {
            while (str[i] != '\0'
                   && str[i] == c) {
                i++;
            }

            if (str[i] != c
                && str[i] != '\0') {
                word_counter++;
            }
        }

        i++;
    }

    return word_counter;
}

