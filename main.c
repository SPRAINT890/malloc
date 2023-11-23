#include "my_malloc_manager.h"

MemoryChunkHeader* first_chunk;
uint16_t id = 0;

int main() {
    
    MemoryChunkHeader* chunk;
    AllocationHeader* header;
    size_t units_needed;
    int option;
    void* puntero_borrar;

    // Imprime el bitmap inicial
    while(true){
        printf("--------------------------------------------------------------\n\n\n");
        printf("1- Allocar bytes\n");
        printf("2- Liberar bytes\n");
        printf("0- Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &option);
        if(option == 1){
            printf("\n--- Allocar Bytes ---\n");
            printf("Ingrese la cantidad de Bytes a allocar: ");
            scanf("%zu", &units_needed);
            void* puntero = my_malloc(units_needed);

            header = (AllocationHeader*)((char*)puntero - sizeof(AllocationHeader));
            chunk = (MemoryChunkHeader*)((char*)header - header->bit_index * UNIT_SIZE);

            printf("El puntero es %p\n", puntero);
            printf("El id del chunk es %u\n", chunk->id);
            printf("El total de unidades del chunk es: %u\n", chunk->chunk_total_units);
            if (!chunk->is_large_allocation){
                printf("Las unidades disponibles en el chunk es: %u\n", chunk->chunk_available_units);
            }
            print_varius_bitmap(first_chunk);
        }
        if(option == 2){
            printf("\n--- Liberar Bytes ---\n");
            printf("Ingrese el puntero del dato a borrar: ");
            scanf("%p", &puntero_borrar);
            my_free(puntero_borrar);
        }
    }
    return 0;
}