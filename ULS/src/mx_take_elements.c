#include "uls.h"

t_list *mx_take_elements(int argc, char *argv[]) {
    t_list *elements = NULL;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-'
            || elements != NULL) {
            mx_push_back(&elements, argv[i]);
        }
    }

    if (elements == NULL) {
        mx_push_back(&elements, ".");
    }

    return elements;
}
