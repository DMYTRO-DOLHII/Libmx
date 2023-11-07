#include <libmx.h> 

static bool is_space(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\r' || c == '\f');
}

char *mx_del_extra_spaces(const char *str) {
    if (str) {        
        char *arr = NULL;
        char *res = NULL;
    
        arr = mx_strnew(mx_strlen(str));
        for (int i = 0, j = 0;str[i]; i++) {
            if (!(is_space(str[i]))) {
                arr[j] = str[i];
                j++;
            }
            if (!(is_space(str[i])) && is_space(str[i + 1])) {
                arr[j] = ' ';
                j++;
            }
            
        }
        res = mx_strtrim(arr);
        mx_strdel(&arr);
        
        return res; 
    }
    return NULL;
}
