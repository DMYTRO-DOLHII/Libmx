#include "libmx.h"

void mx_printint(int n) {
    char a[50];
    long num = n;
    int i = 0;

    if (num < 0) {
        num *= -1;
        mx_printchar('-');
    }

    if (num == 0) {
        mx_printchar(n + '0');
    }

    while (num != 0) {
        a[i++] = (num % 10) + '0';
        num /= 10;
    }

    for (int j = i - 1; j >= 0; j--) {
        mx_printchar(a[j]);
    }
}

