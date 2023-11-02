// my_malloc_manager.h

#ifndef MY_ALLOC_MANAGER_H // prevent multiple includes
#define MY_ALLOC_MANAGER_H 1

// Standard includes
#include <errno.h>  // for errno
#include <error.h>  // for error handling of system calls: man 3 error
#include <stddef.h> // for size_t
#include <stdio.h>  // for I/O functions
#include <stdlib.h> // for EXIT_FAILURE
#include <stdint.h>
#include <stdbool.h> //for true
#include <string.h> // for string manipulation functions

#define BITMAP_SIZE 16 // in bytes

#endif // MY_ALLOC_MANAGER_H
