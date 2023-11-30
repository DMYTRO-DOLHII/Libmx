#include "uls.h"


void mx_arrange_elements(t_list *objects_names, t_sort sort_type) {
    if (sort_type != NONE) {
        mx_sort_list_objects(objects_names, mx_strings_cmp, false);
    }
}
