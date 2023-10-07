#include <libmx.h> 

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int s1_size = mx_strlen(s1);
    int s2_size = mx_strlen(s2);
    int len = s1_size + s2_size;
    int j = 0;

    for(int i = s1_size; i < len; i++) {
        s1[i] = s2[j];
        j++;
    }

    s1[len + 1] = '\0';
    return s1;
}
