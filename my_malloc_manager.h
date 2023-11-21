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
#include <sys/mman.h>

//CONST
#define BITMAP_SIZE (uint16_t)16 // in bytes
#define UNIT_SIZE (uint16_t)16   // minimum unit to assign, in bytes
#define UNITS_PER_CHUNK (uint16_t)(BITMAP_SIZE * 8)
#define STRUCT_UNITS (uint16_t)((sizeof(MemoryChunkHeader) + UNIT_SIZE - 1) / UNIT_SIZE)
#define BITMAP_UNITS (uint16_t)((BITMAP_SIZE + UNIT_SIZE - 1) / UNIT_SIZE)
#define IS_LARGE_ALLOCATION(units) (units >= (UNITS_PER_CHUNK - STRUCT_UNITS + BITMAP_UNITS))
#define MAX_MALLOC_SIZE = (size_t)16 * 1024 * 1024

//declaracion de tipo de estructura
typedef unsigned char *Bitmap;
typedef struct MemoryChunkHeader // All chunks have this header
{
    uint16_t id;                    // id of the chunk, useful for debugging
    uint16_t is_large_allocation;   // Flag to indicate if this is for a single large allocation
    uint16_t chunk_total_units;     // Size of the memory block in units
    uint16_t chunk_available_units; // How many units are available
    Bitmap bitmap;                  // Pointer to the bitmap for this chunk, NULL if is_large_allocation
    uint16_t bitmap_size;           // Size of bitmap in bytes, 0 if is_large_allocation
    struct MemoryChunkHeader *next; // Pointer to the next MemoryChunkHeader, NULL if last one
} MemoryChunkHeader;

typedef struct AllocationHeader // All malloc calls have a this header located before the returned address
{
    uint16_t nunits;    // number of units
    uint16_t bit_index; // offset from the MemoryChunkHeader struct
} AllocationHeader;

//declaracion de funciones
extern int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed);
extern void free_bits(unsigned char *bitmap, size_t bitmap_size, size_t units_to_free, size_t unit_index);
extern void print_bitmap(Bitmap bitmap, uint16_t bitmap_size);
void*create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next);


#endif // MY_ALLOC_MANAGER_H
