#include "my_malloc_manager.h"

/**
 * Modify bits in a bitmap, either setting or clearing them.
 *
 * @param set                 If non-zero, set the bits to 1; otherwise, set them to 0.
 * @param bitmap              The bitmap to modify.
 * @param start_byte_index    The index of the byte where the modification starts.
 * @param start_bit_index     The index of the bit within the byte where the modification starts (0-7).
 * @param qty                 The number of bits to modify.
 */
void set_or_clear_bits(int set, Bitmap bitmap, uint16_t start_byte_index, uint16_t start_bit_index, uint16_t qty)
{
    unsigned char mask; // Mask to isolate target bit within a byte
    uint16_t byte_index, bit_index;
 
    // Loop through the bytes, starting from start_byte_index
    for (byte_index = start_byte_index; qty > 0; byte_index++) {
        mask = 0x80 >> start_bit_index; // 0x80 is binary 1000 0000. Initialize mask based on start_bit_index
        // Loop through the bits within a byte
        for (bit_index = start_bit_index; qty > 0 && bit_index < 8; bit_index++, qty--) {
            if (set) {
                bitmap[byte_index] |= mask; // Set the bit to 1
            } else {
                bitmap[byte_index] &= ~mask; // Set the bit to 0
            }
            mask >>= 1; // Shift mask for next bit
        }
        start_bit_index = 0; // Reset start_bit_index for next byte
    }
}
/*
void set_or_clear_bits(int set, Bitmap bitmap, uint16_t start_byte_index, uint16_t start_bit_index, uint16_t qty) {
    for (uint16_t i = 0; i < qty; i++) {
        unsigned char *current_byte = &bitmap[(start_byte_index + (start_bit_index + i) / 8) % BITMAP_SIZE];
        unsigned char current_bit = 1 << (7 - ((start_bit_index + i) % 8));

        if (set) {
            *current_byte |= current_bit; // Si set es 1, escribimos un 1
        } else {
            *current_byte &= ~current_bit; // Si set es 0, escribimos un 0
        }
    }
}
*/