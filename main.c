#include "my_malloc_manager.h"

int main() {
    unsigned char bitmap[BITMAP_SIZE] = {0};
    size_t units_needed;

    // Imprime el bitmap inicial
    printf("Bitmap inicial: ");
    print_bitmap(bitmap, BITMAP_SIZE);

    while(true){
        printf("Ingrese la cantidad de bits necesarios: ");
        scanf("%zu", &units_needed);
        printf("%zu\n", units_needed);
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