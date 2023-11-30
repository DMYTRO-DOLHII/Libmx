#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    unsigned long number = nbr;
    int i = 0;
    int num_str = nbr;
    int size = 0;

    while (num_str != 0) {
        size++;
        num_str /= 16;
    }

    char *hex_array = mx_strnew(size);

    while (number != 0) {
        int temp = number % 16;

        if (temp < 10) {
            hex_array[i] = temp + 48;
        }
        else {
            hex_array[i] = temp + 87;
        }

        i++;
        number /= 16;
    }

    i--;

    for (int j = 0; j < i; j++, i--) {
        char tmp = hex_array[j];
        hex_array[j] = hex_array[i];
        hex_array[i] = tmp;
    }

    return hex_array;
}

