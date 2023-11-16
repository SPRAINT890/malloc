#include "my_malloc_manager.h"

void print_bitmap(Bitmap bitmap, uint16_t bitmap_size) {
    for (uint16_t i = 0; i < bitmap_size; i++) {
        printf("hola");
        for (uint16_t j = 0; j < 8; j++) {
            if (bitmap[i] & (1 << (7-j))) {
                putchar('1');
            } else {
                putchar('0');
            }
        }
        putchar (i < bitmap_size - 1 ? putchar(' ') : putchar('\n'));
    }
}