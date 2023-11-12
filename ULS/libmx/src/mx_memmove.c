#include <libmx.h>

void *mx_memmove(void *dst, const void *src, size_t len) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;

    if (d > s && d < s + len) {
        d += len - 1;
        s += len - 1;
        while (len--) {
            *d-- = *s--;
        }
    } else {
        while (len--) {
            *d++ = *s++;
        }
    }

    return dst;
}
