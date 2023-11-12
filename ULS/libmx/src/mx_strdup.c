#include <libmx.h>

char *mx_strdup(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    int len = mx_strlen(str);

    char *dupStr = mx_strnew(len);
    mx_strcpy(dupStr, str);

    return mx_strcpy(dupStr, str);;
}
