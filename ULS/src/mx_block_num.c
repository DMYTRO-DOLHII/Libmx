#include "uls.h"

blkcnt_t mx_block_num(t_list *elements) {
    t_list *current = elements;
    blkcnt_t blocks = 0;

    while (current != NULL) {
        t_element *element_data = current->data;

        blocks += element_data->stat.st_blocks;
        current = current->next;
    }

    return blocks;
}
