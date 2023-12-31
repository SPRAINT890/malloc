#include "my_malloc_manager.h"

int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed) {
    size_t consecutive_zeros = 0;
    size_t first_bit_index;

    for (size_t bit_index = 0; bit_index < bitmap_size * 8; bit_index++) {
        size_t byte = bit_index / 8;
        size_t bit = bit_index % 8;
        if ((bitmap[byte] & (1 << (7-bit))) == 0) {
            if (consecutive_zeros == 0){
                first_bit_index = bit_index;
            }
            consecutive_zeros++;
            if (consecutive_zeros == units_needed) {
                set_or_clear_bits(1, bitmap, first_bit_index / 8, first_bit_index % 8, units_needed);
                return first_bit_index;
            }
        } else {
            consecutive_zeros = 0;
        }
    }
    return -1;
}