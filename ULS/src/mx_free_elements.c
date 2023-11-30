#include "uls.h"

void mx_free_elements(t_list *elements_data) {
    t_list *helper = elements_data;

    while (helper != NULL) {
        t_element *element_data = helper->data;
        mx_free_element_data(element_data);
        helper = helper->next;
    }

    mx_clear_list(&elements_data);
}
