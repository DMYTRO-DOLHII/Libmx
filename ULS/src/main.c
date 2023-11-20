#include "../inc/uls.h"

// static void uls_recursive(Directory current_dir, Flag flag) {

// }

static void uls(Directory current_dir, Flag flag) {
    if(flag.R) {
        // uls_recursive(current_dir, flag);
    } else {
        for (int i = 0; i < current_dir.units_count; i++) {
            if (flag.l) {
                print_unit_info(&current_dir.units[i]);
            } else {
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

    // for (int i = 0; i < start_point.units_count; i++) {
    //     if (!flag.G) {
    //         print_unit(start_point.units[i].name, DEFAULT_COLOR);
    //     }
    //     else {
    //         if (start_point.units[i].type == 'd') {
    //             print_unit(start_point.units[i].name, BLUE_COLOR);
    //         }
    //         else {
    //             print_unit(start_point.units[i].name, DEFAULT_COLOR);
    //         }
    //     }
    // }

    mx_printstr("\n");

    return 0;
}
