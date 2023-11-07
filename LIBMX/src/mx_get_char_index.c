#include <libmx.h>

int mx_get_char_index(const char *str, char c) {
    if(str) {
        for(int i = 0; i < mx_strlen(str); i++) {
            if(c == str[i]){
                return i;
            }
        }
        return -1;
    }
    return -2;
}
