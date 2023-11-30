#include "uls.h"

void mx_element_perm_output(mode_t mode) {
    mx_element_type_output(mode);
    mx_printchar((mode & S_IRUSR) ? 'r' : '-');
    mx_printchar((mode & S_IWUSR) ? 'w' : '-');

    if (mode & S_IXUSR) {
        mx_printchar((mode & S_ISUID) ? 's' : 'x');
    } else {
        mx_printchar((mode & S_ISUID) ? 'S' : '-');
    }

    mx_printchar((mode & S_IRGRP) ? 'r' : '-');
    mx_printchar((mode & S_IWGRP) ? 'w' : '-');

    if (mode & S_IXGRP) {
        mx_printchar((mode & S_ISGID) ? 's' : 'x');
    } else {
        mx_printchar((mode & S_ISGID) ? 'S' : '-');
    }

    mx_printchar((mode & S_IROTH) ? 'r' : '-');
    mx_printchar((mode & S_IWOTH) ? 'w' : '-');

    if (mode & S_IXOTH) {
        mx_printchar((mode & S_ISTXT) ? 't' : 'x');
    } else {
        mx_printchar((mode & S_ISTXT) ? 'T' : '-');
    }
}
