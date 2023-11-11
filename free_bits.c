#include "my_malloc_manager.h"

void free_bits(unsigned char *bitmap, size_t bitmap_size, size_t units_to_free, size_t unit_index){
    if(unit_index + units_to_free > bitmap_size * 8){
        return -1;
    }

    for (size_t i = unit_index; i < unit_index + units_to_free && i < bitmap_size * 8; i++) {
        bitmap[i / 8] &= ~(1 << (i % 8));
    }
    printf("Unidades liberadas correctamente.\n");
}
