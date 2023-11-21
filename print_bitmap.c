#include "my_malloc_manager.h"
/*
void print_bitmap(Bitmap bitmap, uint16_t bitmap_size) {
    for (uint16_t i = 0; i < bitmap_size; i++) {
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
*/
void print_bitmap(Bitmap bitmap, uint16_t bitmap_size_in_bytes)
{
    for (uint16_t i = 0; i < bitmap_size_in_bytes; ++i) {
        for (int j = 7; j >= 0; --j) {
            printf("%d", (bitmap[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}