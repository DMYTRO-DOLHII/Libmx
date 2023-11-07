#include <libmx.h>

char *mx_strstr(const char *haystack, const char *needle) {
    int size2 = 0;
    while (needle[size2] != '\0') {
        size2++;
    }

    int size1 = 0;
    while (haystack[size1] != '\0') {
        size1++;
        if (size1 < size2) {
            continue;
        }
        
        int i = 0;
        while (i < size2 && haystack[size1 - size2 + i] == needle[i]) {
            i++;
        }
        
        if (i == size2) {
            return (char*)&haystack[size1 - size2];
        }
    }

    return NULL;
}
