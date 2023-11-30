#include "uls.h"

void mx_sort_by_parameters(t_list *elements_data, t_sort sort_type, bool reverse) {
    switch (sort_type) {
    case NAME:
        mx_sort_list_objects(elements_data, mx_name_cmp, reverse);
        break;

    case TIME:
        mx_sort_list_objects(elements_data, mx_time_cmp, reverse);
        break;

    case SIZE:
        mx_sort_list_objects(elements_data, mx_size_cmp, reverse);
        break;

    default:
        break;
    }
}
