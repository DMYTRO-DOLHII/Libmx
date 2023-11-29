#ifndef ULS_H
#define ULS_H

#include "../libmx/inc/libmx.h"
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

// Colors for output
#define DEFAULT_COLOR "\033[0m"
#define RESET_COLOR "\033[0m"
#define BLUE_COLOR "\033[34m"
#define GREEN_COLOR "\033[32m"
#define CYAN_COLOR "\033[36m"
#define MAGENTA_COLOR "\033[35m"
#define YELLOW_COLOR "\033[33m"

#define ALL_OPTIONS "lRartuUcCbDdfgGhHiIkklmnopqQrsTtuvwxX1@"

#define ACL_TYPE_EXTENDED   0x00000100
#define XATTR_NOFOLLOW      0x0001



typedef struct {
    char name;
} Option;

typedef struct {
    char *name;
} Destination;


typedef struct {
    unsigned long inode;
    char *name;
    char type;
    char *permissions;
    int nlinks;
    char *owner;
    char *group;
    long size;
    char *h_size;
    char *date_time;
    char *symlink;
    char **xattr_keys;
} Unit;

typedef struct {
    char *name;
    int units_count;
    Unit *units;
} Directory;


typedef struct {
    bool a; 
    bool A; 
    bool l; 
    bool r; 
    bool R; 
    bool t; 
    bool u; 
    bool c; 
    bool G; 
    bool h;
    bool e; 
    bool i; 
    bool S; 
    bool T; 
    bool x; 
    bool p; 
    bool d; 
    bool f; 
    bool n; 
    bool g; 
    bool o; 
    bool L; 
    bool F; 
    bool one; // -1
    bool at;  // -@
    bool C; 
    bool B; 
    bool s; 
    bool X; 
    bool v; 
    bool w; 
    bool D; 
    bool P; 
    bool Q; 
} Flag;

typedef struct {
    int nlinks;
    int username;
    int groupname;
    int size;
    int h_size;
} Max_Size;


void print_unit(const char *unit, char *color);
void print_unit_info(Unit *unit, Max_Size *max_size, Flag *flag);
void print_long_list(Directory *current, Flag *flag);

int extract_options(int argc, char *argv[], Option *Options);
int extract_destiations(int argc, char *argv[], Destination *destinations);
void enable_flags(Option *options, int size, Flag *flag);

Directory open_dir(char *name, Flag flag);
Directory open_dir_destinations(char *name, Destination *destinations, int size);
void custom_qsort(void *base, size_t num_elements, size_t element_size, int (*comparator)(const void *, const void *));


#endif

