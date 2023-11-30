#include "uls.h"

t_width mx_maxlen_l(t_list *elements_data, t_flags *flags) {
    t_width width = {.links = 0, .user = 0, .group = 0, .size = 0};

    while (elements_data != NULL) {
        t_element *element_data = elements_data->data;

        char *nlinks = mx_lltoa(element_data->stat.st_nlink);

        if (width.links < mx_strlen(nlinks)) {
            width.links = mx_strlen(nlinks);
        }

        free(nlinks);

        if (width.user < mx_strlen(element_data->user)) {
            width.user = mx_strlen(element_data->user);
        }

        if (width.group < mx_strlen(element_data->group)) {
            width.group = mx_strlen(element_data->group);
        }

        int len_size = 5;

        if (S_ISCHR(element_data->stat.st_mode)
            || S_ISBLK(element_data->stat.st_mode)) {
            char *wsize = mx_nbr_to_hex(element_data->stat.st_rdev);
            len_size = mx_strlen(wsize) + 2;
            free(wsize);
        } else if (!flags->is_h) {
            char *wsize = mx_lltoa(element_data->stat.st_size);
            len_size = mx_strlen(wsize);
            free(wsize);
        }

        if (width.size < len_size) {
            width.size = len_size;
        }

        elements_data = elements_data->next;
    }

    return width;
}
