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
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n\n\n");
        printf("1- Allocar bytes\n");
        printf("2- Liberar bytes\n");
        printf("0- Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &option);
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------\n\n\n");
        if(option == 1){
            printf("--- Allocar Bytes ---\n");
            printf("Ingrese la cantidad de Bytes a allocar: ");
            scanf("%zu", &units_needed);
            void* puntero = my_malloc(units_needed);

            header = (AllocationHeader*)((char*)puntero - sizeof(AllocationHeader));
            chunk = (MemoryChunkHeader*)((char*)header - header->bit_index * UNIT_SIZE);
            printf("\n--------------------------------\n");
            printf("| El puntero es %p |", puntero);
            printf("\n--------------------------------\n");
            printf("\nEl total de unidades del chunk %u es: %u\n", chunk->id, chunk->chunk_total_units);
            if (!chunk->is_large_allocation){
                printf("Las unidades disponibles del chunk %u es: %u\n", chunk->id, chunk->chunk_available_units);
            }
            print_varius_bitmap(first_chunk);
        }
        else if(option == 2){
            printf("--- Liberar Bytes ---\n");
            printf("Ingrese el puntero del dato a borrar: ");
            scanf("%p", &puntero_borrar);
            my_free(puntero_borrar);
        }
        else{
            return 0;
        }
    }
    return 0;
}