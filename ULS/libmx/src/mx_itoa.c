#include "libmx.h"

static int number_length(int number) {
    int i = 0;

    while (number) {
        number /= 10;
        i++;
    }

    return i;
}

char *mx_itoa(int number) {
    int length = number_length(number);
    char *string = NULL;
    string = mx_strnew(length);

    if (number == 0) {
        return mx_strcpy(string, "0");
    }

    if (number == -2147483648) {
        return mx_strcpy(string, "-2147483648");
    }

    int temp = number;

    for (int i = 0; i < length; i++) {
        if (temp < 0) {
            string[length] = '-';
            temp = -temp;
        }

        string[i] = (temp % 10) + '0';
        temp /= 10;
    }

    mx_str_reverse(string);

    return string;
}

