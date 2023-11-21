#include "my_malloc_manager.h"

void set_or_clear(int set, Bitmap bitmap, uint16_t cantidad, uint16_t byte_inicio , uint16_t bit_inicio){
    for (uint16_t i = 0; i < cantidad; i++) {
        unsigned char *byte_actual = &bitmap[(byte_inicio + (bit_inicio + i) / 8) % BITMAP_SIZE];
        unsigned char bit_actual = 1 << (7 - ((bit_inicio + i) % 8));

        if (set){
            *byte_actual |= bit_actual;
        } else{
            *byte_actual &= ~bit_actual;
        }
    }
}
