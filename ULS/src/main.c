#include "../inc/uls.h"

int compare(const void *a, const void *b) {
    return strcmp(((Unit *)a)->name, ((Unit *)b)->name);
}

static char *get_pemissions(mode_t mode) {
    char permission[11];

    permission[0] = S_ISDIR(mode) ? 'd' : '-';
    permission[1] = mode & S_IRUSR ? 'r' : '-';
    permission[2] = mode & S_IWUSR ? 'w' : '-';
    permission[3] = mode & S_IXUSR ? 'x' : '-';
    permission[4] = mode & S_IRGRP ? 'r' : '-';
    permission[5] = mode & S_IWGRP ? 'w' : '-';
    permission[6] = mode & S_IXGRP ? 'x' : '-';
    permission[7] = mode & S_IROTH ? 'r' : '-';
    permission[8] = mode & S_IWOTH ? 'w' : '-';
    permission[9] = mode & S_IXOTH ? 'x' : '-';
    permission[10] = '\0';

    return mx_strdup(permission);
}

static Directory open_dir(char *name){

    int units_count = 0;

    // Find units number in the directory
    DIR *dir = opendir(name);
    if (dir == NULL) {
        perror("Error opening directory");
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        units_count++;
    }
    closedir(dir);

    // Create units
    Unit *units = (Unit*)malloc(units_count * sizeof(Unit));
    int i = 0;

    dir = opendir(name);
    if (dir == NULL) {
        perror("Error opening directory");
    }

    while ((entry = readdir(dir)) != NULL) {
        struct stat file_stat;
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("Error getting file stat");
            continue;
        }

        units[i].name = entry->d_name;
        // ----- type

        if (S_ISDIR(file_stat.st_mode)) units[i].type = 'd';
        else if (S_ISLNK(file_stat.st_mode)) units[i].type = 'l';
        else if (S_ISCHR(file_stat.st_mode)) units[i].type = 'c';
        else if (S_ISFIFO(file_stat.st_mode)) units[i].type = 'p';
        else if (S_ISBLK(file_stat.st_mode)) units[i].type = 'b';
        else units[i].type = '-';

        // -----------

        units[i].permissions = get_pemissions(file_stat.st_mode);
        units[i].nlinks = file_stat.st_nlink;
        units[i].owner = getpwuid(file_stat.st_uid)->pw_name;
        units[i].group = getgrgid(file_stat.st_gid)->gr_name;
        units[i].size = file_stat.st_size;
        units[i].modification_time = "";
        units[i].nlinks = file_stat.st_nlink;

        i++;
    }

    custom_qsort(units, units_count, sizeof(Unit), compare);

    Directory current = {name, units_count, units};

    // Close the directory
    closedir(dir);

    return current;
}

int main(int argc, char* argv[]) {    
    Flag flag = { false };
    Option *options = (Option*)malloc(sizeof(Option));
    Destination *destinations = (Destination*)malloc(sizeof(Destination));


    int num_options = extract_options(argc, argv, options);
    int num_destinations = extract_destiations(argc, argv, destinations);

    enable_flags(options, num_options, flag);


    num_options++;
    num_destinations++;

    Directory start_point = open_dir(".");

    for (int i = 0; i < start_point.units_count; i++) {
        if (start_point.units[i].type == 'd') {
            print_unit(start_point.units[i].name, BLUE_COLOR);
        } else {
            print_unit(start_point.units[i].name, DEFAULT_COLOR);
        }

    }

    mx_printstr("\n");

    return 0;
}
