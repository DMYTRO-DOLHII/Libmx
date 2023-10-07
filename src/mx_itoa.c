#include <libmx.h>

char *mx_itoa(int number) {
    int length = 0;
    int num = number;

    if (number == -2147483648) {
        return mx_strdup("-2147483648");
    }
    else if (number == 0) {
        return mx_strdup("0");
    }
    
    while (num) {
        num /= 10;
        length++;
    }

    char *result = mx_strnew(length + 1); 
    if (number < 0) {
        result[0] = '-';
        number = -number;
    }

    int i = length - 1;
    while (number > 0) {
        result[i] = '0' + number % 10;
        number /= 10;
        i--;
    }
    return result;
}
