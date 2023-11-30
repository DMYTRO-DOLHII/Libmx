#include "uls.h"

int mx_element_inf_output(t_element *object_info, t_flags *flags) {
    if (flags->is_G) {
        mx_element_color_output(object_info->stat.st_mode);
    }

    mx_element_name_output(object_info->name, flags->is_q);

    if (flags->is_G) {
        mx_printstr("\033[0m");
    }

    int counter = mx_strlen(object_info->name);

    if (flags->is_F
        || flags->is_p) {
        counter += mx_element_class_output(object_info->stat.st_mode, flags->is_p);
    }

    return counter;
}
