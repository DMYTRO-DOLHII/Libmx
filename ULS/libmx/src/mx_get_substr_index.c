#include <libmx.h>

int mx_get_substr_index(const char *str, const char *sub) {
    if (sub && str) {
        int index = 0;
        
        while (*str) {
            int i = 0;
            while (sub[i] != '\0' && str[i] == sub[i]) {
                i++;
            }

            if (sub[i] == '\0') {
                return index;
            }

            index++;
            str++;
        }
        return -1;
    }
    return -2;
}
