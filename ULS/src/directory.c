#include "../inc/uls.h"

int compare(const void *a, const void *b) {
    return strcmp(((Unit *)a)->name, ((Unit *)b)->name);
}

void append_str(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
}

void append_num(char *dest, int num) {
    // Convert each digit to a character and append
    if (num >= 10) {
        append_num(dest, num / 10);
    }
    *dest = '0' + (num % 10);
    dest++;
}

char *format_time(const struct stat *file_stat) {
    struct tm *tm_info;

    // Extract the modification time from the struct stat
    time_t mtime = file_stat->st_mtime;

    // Convert the modification time to the local time
    tm_info = localtime(&mtime);

    // Check if the conversion was successful
    if (tm_info == NULL) {
        perror("Error converting time");
        exit(EXIT_FAILURE);
    }

    // Define arrays for month abbreviations and the formatted time string
    static const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // Allocate memory for the formatted time string
    char *time_str = (char *)malloc(20); // You need to free this memory when done

    // Check if memory allocation was successful
    if (time_str == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    // Format the time string manually
    append_str(time_str, months[tm_info->tm_mon]);
    append_str(time_str, " ");
    append_num(time_str, tm_info->tm_mday);
    append_str(time_str, " ");
    append_num(time_str, tm_info->tm_hour);
    append_str(time_str, ":");
    append_num(time_str, tm_info->tm_min);

    return time_str;
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

static void set_unit(Unit *unit, struct dirent *entry, struct stat file_stat) {
    unit->name = entry->d_name;
    if (S_ISDIR(file_stat.st_mode)) unit->type = 'd';
    else if (S_ISLNK(file_stat.st_mode)) unit->type = 'l';
    else if (S_ISCHR(file_stat.st_mode)) unit->type = 'c';
    else if (S_ISFIFO(file_stat.st_mode)) unit->type = 'p';
    else if (S_ISBLK(file_stat.st_mode)) unit->type = 'b';
    else unit->type = '-';
    unit->permissions = get_pemissions(file_stat.st_mode);
    unit->nlinks = file_stat.st_nlink;
    unit->owner = getpwuid(file_stat.st_uid)->pw_name;
    unit->group = getgrgid(file_stat.st_gid)->gr_name;
    unit->size = file_stat.st_size;
    unit->modification_time = "TIME";
    unit->nlinks = file_stat.st_nlink;
    // symlink
    if (S_ISLNK(file_stat.st_mode)) {
        char link_target[1024];  
        ssize_t len = readlink(entry->d_name, link_target, sizeof(link_target) - 1);
        if (len != -1) {
            link_target[len] = '\0'; 
            unit->symlink = mx_strdup(link_target);  
        } else {
            perror("Error reading symlink target");
            exit(EXIT_FAILURE);
        }
    } else {
        // It's not a symlink
        unit->symlink = NULL;
    }
}

Directory open_dir(char *name, Flag flag) {

    int units_count = 0;

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


        if (!flag.a) {
            if (!flag.A) {
                if (entry->d_name[0] == '.') continue;
            } else {
                if (mx_strcmp(entry->d_name, ".") == 0 || mx_strcmp(entry->d_name, "..") == 0) continue;
            }
        }

        // Set unit ------------------------
        set_unit(&units[i], entry, file_stat);
        // ---------------------------------

        i++;
    }


    custom_qsort(units, i, sizeof(Unit), compare);

    Directory current = {name, i, units};
    closedir(dir);

    return current;
}

Directory open_dir_destinations(char *name, Destination *destinations, int size) {
    DIR *dir;
    Unit *units = (Unit*)malloc(size * sizeof(Unit));
    int i = 0;

    for (int j = 0; j < size; j++) {
        bool exist = false;

        struct dirent *entry;

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

            if (mx_strcmp(destinations[j].name, entry->d_name) == 0) {
                // Set unit ------------------------
                set_unit(&units[i], entry, file_stat);
                // ---------------------------------

                i++;
                exist = true;
                break;
            }
        }

        if (!exist) {
            mx_printerr("uls: cannot access '");
            mx_printstr(destinations[j].name);
            mx_printstr("': No such file or directory\n");
            exit(1);
        }
    }

    custom_qsort(units, size, sizeof(Unit), compare);

    Directory current = {name, size, units};
    closedir(dir);

    return current;
}

