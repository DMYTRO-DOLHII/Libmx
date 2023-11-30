#include "uls.h"

void mx_onecol_output(t_list *elements_data, t_flags *flags) {
    while (elements_data != NULL) {
        mx_element_inf_output(elements_data->data, flags);
        mx_printchar('\n');
        elements_data = elements_data->next;
    }
}
