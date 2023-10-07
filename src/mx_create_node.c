#include <libmx.h>

t_list *mx_create_node(void *data) {
    if (!data)
        return NULL;

    t_list *new = NULL;
    new = (t_list *) malloc(sizeof(t_list));
    
    if (!new)
        return NULL;

    new->data = data;
    new->next = NULL;
    return new;
}
