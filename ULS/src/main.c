#include "uls.h"








int main(int argc, char *argv[]) {

    t_list *elements = mx_take_elements(argc, argv);

    int val1 = mx_validate_elements(elements);

    if (val1 < 0)
    {
        return -1;
    }

    t_flags *flags = mx_init_flags(argc, argv);

    int val2 = 0;
    val2 = mx_validate_flags(flags); 

    if (val2 < 0)
    {
        return -1;
    }

    int result = mx_output_elements(elements, flags);

    mx_clear_list(&elements);
    
    free(flags);

    return result;
}
