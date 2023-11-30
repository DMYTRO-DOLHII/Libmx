#include "libmx.h"

t_list *mx_sort_list_objects(t_list *list, bool (*cmp)(void *, void *), bool reverse) {
    if (list == NULL
        || cmp == NULL) {
        return list;
    }

    bool sorted = false;

    while (!sorted) {
        sorted = true;

        for (t_list *i = list; i->next != NULL; i = i->next) {
            bool cmp_nodes = cmp(i->data, i->next->data);
            if ((cmp_nodes
                && !reverse)
                || (!cmp_nodes
                    && reverse)) {
                void *temp_data = i->data;
                i->data = i->next->data;
                i->next->data = temp_data;
                sorted = false;
            }
        }
    }

    return list;
}

