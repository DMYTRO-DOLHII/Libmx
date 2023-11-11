#include "../inc/pathfinder.h"

int island_index(Island *islands, int size, char *name) {
	for (int i = 0; i < size; i++) {
		if (mx_strcmp(islands[i].name, name) == 0) return i;
	}

	return -1;
}

