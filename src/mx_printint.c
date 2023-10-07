#include <libmx.h>

void mx_printint(int n) {
    if (n == -2147483648) {
        write(1, "-2147483648", 11);
        return;
    }

    if (n < 0) {
        mx_printchar('-');
        n = -n;
    }

    char buffer[12];
    int i = 0;

    do {
        buffer[i++] = n % 10 + '0';
        n /= 10;
    } while (n > 0);

    while (--i >= 0) {
        mx_printchar(buffer[i]);
    }
}
