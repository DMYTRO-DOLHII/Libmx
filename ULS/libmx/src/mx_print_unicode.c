#include "libmx.h"

void mx_print_unicode(wchar_t c) {
    if (c < 0x80) {
        char array[1];
        array[0] = (c >> 0 & 0x7F) | 0x00;
        write(1, array, 1);
    }
    else if (c < 0x0800) {
        char array[2];
        array[0] = (c >> 6 & 0x1F) | 0xC0;
        array[1] = (c >> 0 & 0x3F) | 0x80;
        write(1, array, 2);
    }
    else if (c < 0x010000 ) {
        char array[3];
        array[0] = (c >> 12 & 0x0F) | 0xE0;
        array[1] = (c >> 6 & 0x3F) | 0x80;
        array[2] = (c >> 0 & 0x3F) | 0x80;
        write(1, array, 3);
    }
    else {
        char array[4];
        array[0] = (c >> 18 & 0x07) | 0xF0;
        array[1] = (c >> 12 & 0x3F) | 0x80;
        array[2] = (c >> 6 & 0x3F) | 0x80;
        array[3] = (c >> 0 & 0x3F) | 0x80;
        write(1, array, 4);
    }
}

