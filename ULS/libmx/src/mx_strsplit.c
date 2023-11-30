#include "libmx.h"

static void mx_str_to_arr(char const *s, char c, char **array) {
    int word_length = 0;
    int index = 0;
    int j = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != c
            && word_length == 0) {
            index = i;
        }

        if (s[i] != c
            && s[i] != 0) {
            word_length++;
        }

        if (word_length > 0
            && (s[i + 1] == c
                || s[i + 1] == 0)) {
            array[j] = mx_strnew(word_length);
            array[j] = mx_strncpy(array[j], &(s[index]), word_length);
            word_length = 0;
            j++;
        }
    }

    array[j] = NULL;
}

char **mx_strsplit(char const *s, char c) {
    if (s == NULL) {
        return NULL;
    }

    char **array = NULL;
    array = (char **) malloc(sizeof(char *) * (mx_count_words(s, c) + 1));
    mx_str_to_arr(s, c, array);

    return array;
}

