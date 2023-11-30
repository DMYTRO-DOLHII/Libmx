#include "uls.h"

void mx_element_type_output(mode_t mode) {
    if ((mode & S_IFMT) == S_IFBLK) {
        mx_printchar('b');
    } else if ((mode & S_IFMT) == S_IFCHR) {
        mx_printchar('c');
    } else if ((mode & S_IFMT) == S_IFDIR) {
        mx_printchar('d');
    } else if ((mode & S_IFMT) == S_IFIFO) {
        mx_printchar('p');
    } else if ((mode & S_IFMT) == S_IFLNK) {
        mx_printchar('l');
    } else if ((mode & S_IFMT) == S_IFSOCK) {
        mx_printchar('s');
    } else {
        mx_printchar('-');
    }
}
