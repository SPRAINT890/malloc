#include "my_malloc_manager.h"
//#include "functions/first_fit.c"
//#include "functions/print_bitmap.c"

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

int main() {
    unsigned char bitmap[BITMAP_SIZE] = {0};
    size_t units_needed;

    // Imprime el bitmap inicial
    printf("Bitmap inicial: ");
    print_bitmap(bitmap, BITMAP_SIZE);

    while(true){
        printf("Ingrese la cantidad de bits necesarios: ");
        scanf("%zu", &units_needed);

        int index = first_fit(bitmap, BITMAP_SIZE, units_needed);

        if (index != -1) {
            printf("Se asignaron %zu bits a partir del índice %d.\n", units_needed, index);
            printf("Bitmap después de la asignación: ");
            print_bitmap(bitmap, BITMAP_SIZE);
        } else {
            printf("No hay suficiente espacio para asignar %zu bits.\n", units_needed);
            break;
        }
    }
    return 0;
}