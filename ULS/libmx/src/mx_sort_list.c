#include "libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    if (lst == NULL
        || cmp == NULL) {
        return lst;
    }

    int size = mx_list_size(lst);

    for (int i = 0; i < size; i++) {
        t_list *current_list = lst;

        for (int j = 0; j < size - 1; j++) {
            if (cmp(current_list->data, current_list->next->data)) {
                void *temp = current_list->data;
                current_list->data = current_list->next->data;
                current_list->next->data = temp;
            }

            current_list = current_list->next;
        }
    }

    return lst;
}

