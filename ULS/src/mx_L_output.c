#include "uls.h"

void mx_L_output(t_list *elements_data, t_flags *flags) {
    t_width width = mx_maxlen_l(elements_data, flags);

    while (elements_data != NULL) {
        mx_L_output_single(elements_data->data, &width, flags);
        elements_data = elements_data->next;
    }
}

