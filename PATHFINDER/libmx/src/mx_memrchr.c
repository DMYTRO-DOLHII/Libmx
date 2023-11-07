#include <libmx.h>

void *mx_memrchr(const void *s, int c, size_t n){
    const unsigned char *p = (const unsigned char *)s;

    for (size_t i = n; i > 0; i--) {
        if (p[i - 1] == (unsigned char)c) {
            return (void *)(p + i - 1);
        }
    }

    return NULL;
}
