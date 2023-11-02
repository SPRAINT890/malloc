#include "my_malloc_manager.h"

void print_bitmap(unsigned char *bitmap, size_t bitmap_size) {
    for (size_t i = 0; i < bitmap_size; i++) {
        for (size_t j = 0; j < 8; j++) {
            if (bitmap[i] & (1 << (7-j))) {
                putchar('1');
            } else {
                putchar('0');
            }
        }
        putchar (i < bitmap_size - 1 ? putchar(' ') : putchar('\n'));
    }
}