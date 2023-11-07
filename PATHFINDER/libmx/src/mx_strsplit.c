#include <libmx.h>

char **mx_strsplit(const char *s, char c) {
    if (s == NULL)
        return NULL;

    int num_words = mx_count_words(s, c);
    char **result = (char **)malloc(8 * (num_words + 1));

    if (result) {
        const char *start = s;
        int word_index = 0;
        bool in_word = false;

        while (*s) {
            if (*s == c) {
                if (in_word) {
                    int word_len = s - start;
                    result[word_index++] = mx_strndup(start, word_len);
                    in_word = false;
                }
            } else {
                if (!in_word) {
                    start = s;
                    in_word = true;
                }
            }
            s++;
        }

        if (in_word) {
            int word_len = s - start;
            result[word_index++] = mx_strndup(start, word_len);
        }

        result[num_words] = NULL;
    }

    return result;
}
