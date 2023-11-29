#include "../inc/uls.h"

// static void uls_recursive(Directory current_dir, Flag flag) {

// }

static void uls(Directory current_dir, Flag flag) {
    if(flag.R) {
        // uls_recursive(current_dir, flag);
    } else {
        if (flag.l) {
            print_long_list(&current_dir, &flag);
        } else {
            for (int i = 0; i < current_dir.units_count; i++){
                print_unit(current_dir.units[i].name, DEFAULT_COLOR);
            }
        }
    }

}

int main(int argc, char *argv[]) {
    Flag flag = {false};
    Option *options = (Option *)malloc(sizeof(Option));
    Destination *destinations = (Destination *)malloc(sizeof(Destination));

    int num_options = extract_options(argc, argv, options);
    int num_destinations = extract_destiations(argc, argv, destinations);

    enable_flags(options, num_options, &flag);

    Directory start_point;

    if (num_destinations != 0) {
        start_point = open_dir_destinations(".", destinations, num_destinations);
    }
    else {
        start_point = open_dir(".", flag);
    }

    uls(start_point, flag);

    mx_printstr("\n");

    return 0;
}
