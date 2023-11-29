#include <libmx.h>

char* mx_utoa(unsigned long num) {
    char* r = NULL;
    int digits = 0;
    unsigned long temp = num;

    do {
        digits++;
        temp /= 10;
    } while (temp > 0);

    r = (char*)malloc(digits + 1); 

    if (r == NULL) {
        perror("malloc");
        exit(1);
    }

    int i = digits - 1;
    do {
        r[i--] = (num % 10) + '0';
        num /= 10;
    } while (num > 0);

    r[digits] = '\0'; 

    return r;
}