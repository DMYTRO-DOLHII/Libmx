#include <libmx.h>

char *mx_nbr_to_hex(unsigned long nbr) {
    char *result = NULL;
    unsigned long num = nbr;
    int len = 0;

    while (num) {
        num /= 16;
        len++;
    }

    num = nbr;
    int temp;
    result = malloc(len);

    if (nbr == 0)
        return mx_strcpy(result, "0");
    while (num) {
        temp = num % 16;
        if (temp < 10)
            result[--len] = 48 + temp;
        if (temp >= 10)
            result[--len] = 87 + temp;
        num /= 16;
    }
    return result;
}
