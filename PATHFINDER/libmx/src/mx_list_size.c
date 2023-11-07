#include <libmx.h>

int mx_list_size(t_list *list) {
    if (list == NULL)
        return 0;

    int size = 1;
    t_list *temp = list;

    while (temp -> next != NULL) {
        size++;
        temp = temp -> next;
    }
    return size;
}
