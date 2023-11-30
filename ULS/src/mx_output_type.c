#include "uls.h"

void mx_output_type(t_list *elements_data, t_flags *flags) {
    if (flags->format == ONECOL_OUTPUT) {
        mx_onecol_output(elements_data, flags);
    } else if (flags->format == DEFAULT_OUTPUT) {
        mx_default_output(elements_data, flags);
    } else if (flags->format == ONEROW_OUTPUT) {
        mx_onerow_output(elements_data, flags);
    } else if (flags->format == L_OUTPUT) {
        mx_L_output(elements_data, flags);
    } 
}
