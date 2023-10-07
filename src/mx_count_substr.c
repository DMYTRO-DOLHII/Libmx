#include <libmx.h>

int mx_count_substr(const char *str, const char *sub) {
    int i = 0;

    if (str == NULL || sub == NULL)
        return -1;

    int str_len = mx_strlen(str);
    int sub_len = mx_strlen(sub);

    if (str_len >= sub_len) {
        while (*str) {
            int j = 0;
            while (j < sub_len && str[j] == sub[j]) {
                j++;
            }

            if (j == sub_len) {
                i++;
            }

            str++;
        }
    }

    return i;
}
