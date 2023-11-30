#include "uls.h"

void mx_onerow_output(t_list *elements_data, t_flags *flags) {
    while (elements_data != NULL) {
        mx_element_inf_output(elements_data->data, flags);

        if (elements_data->next != NULL) {
            mx_printstr(", ");
        }

        elements_data = elements_data->next;
    }

    mx_printchar('\n');
}
