#include "my_malloc_manager.h"

void free_bits(unsigned char *bitmap, size_t bitmap_size, size_t units_to_free, size_t unit_index){
    for (size_t i = unit_index; i < unit_index + units_to_free && i < bitmap_size * 8; i++) {
        size_t byte = i / 8;
        bitmap[byte] &= ~(1 << (7 -(i % 8)));
    }
}