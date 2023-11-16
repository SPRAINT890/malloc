#include "my_malloc_manager.h"

int main() {
    MemoryChunkHeader* chunk = create_new_chunk(BITMAP_SIZE, 0, 0);

    size_t units_needed;
    size_t units_remove;
    size_t units_index;
    int option;

    // Imprime el bitmap inicial
    printf("Bitmap inicial: \n");
    print_bitmap(chunk->bitmap, chunk->bitmap_size);

    while(true){
        printf("1- Agregar bits\n");
        printf("2- Quitar bits\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &option);
        if(option == 1){
            printf("\n--- Agregar Bits ---\n");
            printf("Ingrese la cantidad de bits necesarios: ");
            scanf("%zu", &units_needed);
            printf("%zu\n", units_needed);
            int index = first_fit(chunk->bitmap, chunk->bitmap_size, units_needed);

            if (index != -1) {
                printf("Se asignaron %zu bits a partir del índice %d.\n", units_needed, index);
                printf("Bitmap después de la asignación: ");
                print_bitmap(chunk->bitmap, chunk->bitmap_size);
            } else {
                printf("No hay suficiente espacio para asignar %zu bits.\n", units_needed);
                break;
            }
        }
        else{
            printf("\n--- Quitar Bits ---\n");
            printf("Ingrese el bit de comienzo: ");
            scanf("%zu", &units_index);
            printf("\nIngrese la cantidad de bits a borrar: ");
            scanf("%zu", &units_remove);
            if(units_index + units_remove > BITMAP_SIZE * 8){
                printf("\nBits fuera de rango\n");
                return 0;
            }       
            free_bits(chunk->bitmap, chunk->bitmap_size, units_remove, units_index);

            printf("\nSe Quitaron %zu bits a partir del índice %zu.\n", units_remove, units_index);
            printf("Bitmap después de borrar: ");
            print_bitmap(chunk->bitmap, chunk->bitmap_size);
        }
    }
    return 0;
}