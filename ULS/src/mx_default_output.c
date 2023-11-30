#include "uls.h"

void mx_default_output(t_list *elements_data, t_flags *flags) {
    int tab_len = 8;

    if (flags->is_G) {
        tab_len = 1;
    }

    int len = mx_maxlen_default(elements_data);

    if (flags->is_F || flags->is_p) {
        len++;
    }

    len = (len + tab_len) & ~(tab_len - 1);

    int cols_n = mx_find_space_len() / len;

    if (cols_n <= 1) {
        mx_onecol_output(elements_data, flags);
        return;
    }

    int counter;
    t_element **array = mx_create_arr_from_list(elements_data, &counter);
    int rows_n = (counter + cols_n - 1) / cols_n;
    int index = 0;

    for (int i = 0; i < rows_n; i++) {
        if (!flags->is_x) {
            index = i;
        }

        for (int j = 0; j < cols_n; j++) {
            int printed = mx_element_inf_output(array[index], flags);

            if (flags->is_x) {
                index++;
            } else {
                index += rows_n;
            }

            if (index >= counter) {
                break;
            }

            mx_cols_output(len - printed, tab_len);
        }

        mx_printchar('\n');
    }

    if (array != NULL) {
        free(array);
    }
}
