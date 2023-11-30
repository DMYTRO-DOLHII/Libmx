#include "uls.h"

void mx_element_color_output(mode_t mode) {
   if ((mode & S_IFMT) == S_IFBLK) {
        mx_printstr("\033[34;46m");
    } else if ((mode & S_IFMT) == S_IFCHR) {
        mx_printstr("\033[34;43m");
    } else if ((mode & S_IFMT) == S_IFDIR) {
        if (mode & S_IWOTH) {
            if (mode & S_ISTXT) {
                mx_printstr("\033[30;42m");
            } else {
                mx_printstr("\033[30;43m");
            }
        } else {
            mx_printstr("\033[34m");
        }
    } else if ((mode & S_IFMT) == S_IFIFO) {
        mx_printstr("\033[33m");
    } else if ((mode & S_IFMT) == S_IFLNK) {
        mx_printstr("\033[35m");
    } else if ((mode & S_IFMT) == S_IFSOCK) {
        mx_printstr("\033[32m");
    } else {
        if (mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
            if (mode & S_ISUID) {
                mx_printstr("\033[30;41m");
            } else if (mode & S_ISGID) {
                mx_printstr("\033[30;46m");
            } else {
                mx_printstr("\033[31m");
            }
        }
    }
}
