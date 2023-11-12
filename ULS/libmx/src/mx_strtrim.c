#include <libmx.h>

static bool is_space(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\r' || c == '\f');
}

char *mx_strtrim(const char *str) {
    if(str) {
        int len = 0;
        char *new = NULL;

        while (is_space(*str))
            str++;
        len = mx_strlen(str);
        while (len > 0 && is_space(str[len - 1]))
            len--;
        new = mx_strndup(str, len);
        return new;
    }
    return NULL;
}
