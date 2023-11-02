int first_fit(unsigned char *bitmap, size_t bitmap_size, size_t units_needed) {
    int consecutive_zeros = 0;
    int index = -1;

    for (int i = 0; i < bitmap_size * 8; i++) {
        if ((bitmap[i / 8] & (1 << (i % 8))) == 0) {
            consecutive_zeros++;
            if (consecutive_zeros == units_needed) {
                index = i - units_needed + 1;
                for (int j = 0; j < units_needed; j++) {
                    bitmap[index / 8] |= (1 << (index % 8));
                    index++;
                }
                break;
            }
        } else {
            consecutive_zeros = 0;
        }
    }

    return index;
}