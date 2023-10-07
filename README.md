# libmx

libmx is a custom C library developed to provide a wide range of useful functions for various tasks.

## Table of Contents
- [Description](#description)
- [Functions](#functions)
- [Usage](#usage)
- [How to Compile](#how-to-compile)
- [Contributing](#contributing)
- [License](#license)

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

For a complete list of functions, refer to the [documentation](#documentation).

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
To compile your C code with libmx, include the library during the compilation process. For example, if your source file is main.c:

```c
gcc main.c -o my_program
```

This command links your code with libmx (-L. specifies the current directory, and -lmx links with libmx) and creates an executable named my_program.

## Contributing
Contributions are welcome! If you find any issues or have improvements to suggest, please create an issue or a pull request.

