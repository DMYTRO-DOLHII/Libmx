#include "libmx.h"

char *mx_strjoin_with_delim(const char *s1, const char *s2, char delim) {
    if (s1 == NULL) {
        return mx_strdup(s2);
    }

    int str1_len = mx_strlen(s1);
    int str2_len = mx_strlen(s2);
    char *string = mx_strnew(str1_len + str2_len + 1);
    mx_strcpy(string, s1);
    string[str1_len] = delim;
    mx_strcpy(string + str1_len + 1, s2);

    return string;
}

