# libmx

libmx is a custom C library developed to provide a wide range of useful functions for various tasks.

## Description
libmx contains a collection of functions for string manipulation, memory management, sorting algorithms, and more. It is designed to simplify C programming by providing efficient and reliable implementations of common operations.

## Functions
The library includes functions such as:
- `mx_strlen` - Get the length of a string.
- `mx_strcmp` - Compare two strings.
- `mx_strcpy` - Copy a string.
- `mx_itoa` - Convert an integer to a string.
- `mx_bubble_sort` - Sort an array using the bubble sort algorithm.
- ...and many more.

For a complete list of functions, refer to the [code](https://github.com/DMYTRO-DOLHII/Libmx/tree/master/src).

## Usage
To use libmx in your C projects, include the `libmx.h` header file in your source files.

Example:
```c
#include <libmx.h>

int main() {
    char str[] = "Hello, libmx!";
    int length = mx_strlen(str);
    printf("Length of the string: %d\n", length);
    return 0;
}
```

## How to Compile
```bash
make
```

-------------------------------------------------------------------------------------------------------------------------------------------------------
# Pathfinder
Pathfinder is a C-based project designed to parse files containing graph data, create an adjacency matrix to represent the relationships between nodes, and perform pathfinding operations. The project offers functionality to store the matrix, find the shortest path from one point (A) to another (B), as well as identify alternative routes.

## Features
- File Parsing: Pathfinder can efficiently parse files containing graph data, extracting essential information to build a representation of the graph.
- Adjacency Matrix: The project employs an adjacency matrix to store and manage the relationships between nodes in the graph, providing a clear and efficient structure for pathfinding.
- Matrix Storage: Pathfinder allows users to store the generated adjacency matrix for future reference or analysis.
- Pathfinding: The core functionality includes finding the shortest path from a specified starting point (A) to a destination point (B) within the graph.
- Alternative Routes: In addition to the shortest path, the project offers the capability to identify alternative routes between two points, providing flexibility in navigation.
- Output Printing: Pathfinder facilitates the printing of pathfinding results, making it easy for users to visualize and analyze the discovered paths.

## Usage
1. Go to PATHFINDER dir
   ```cd PATHFINDER/```
2. Build project
   ```make```
3. Run ./pathfinder. Test files located in /PATHFINDER/test/
   ```./pathfinder test/easy```

-------------------------------------------------------------------------------------------------------------------------------------------------------

# uls
uls is a C-based implementation inspired by the Unix command ls. It is designed to list information about files and directories in a user-friendly and customizable manner.

## Features
- Directory Listing: uls provides a clear and organized listing of files and directories within a specified directory.
- File Information: Detailed information about each file, including permissions, owner, size, and modification time, is displayed for comprehensive file analysis.
- Sorting Options: Users can customize the display by sorting files based on various criteria, such as name, size, or modification time.
- Colorized Output: Enhance visibility with colorized output, allowing users to quickly identify file types and statuses.
- Filtering: Filter the displayed files based on specified criteria, making it easy to focus on specific subsets of files.
- Recursive Listing: uls supports recursive listing, providing a complete overview of files within subdirectories.

## Usage
1. Go to ULS dir
   ```cd ULS/```
2. Build project
   ```make```
3. Run ./uls. You can also use the same flags as `ls` command
   ```./uls -la```
