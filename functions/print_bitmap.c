void print_bitmap(unsigned char *bitmap, size_t bitmap_size) {
    for (int i = 0; i < bitmap_size; i++) {
        for (int j = 7; j >= 0; j--) {
            if (bitmap[i] & (1 << j)) {
                putchar('1');
            } else {
                putchar('0');
            }
        }
        if (i < bitmap_size - 1) {
            putchar(' ');
        }
    }
    putchar('\n');
}