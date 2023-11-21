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
        printf("1- Agregar bits\n");
        printf("2- Quitar bits\n");
        printf("0- Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &option);
        if(option == 1){
            printf("\n--- Agregar Bits ---\n");
            printf("Ingrese la cantidad de bits necesarios: ");
            scanf("%zu", &units_needed);
            void* puntero = my_malloc(units_needed);

            header = (AllocationHeader*)((char*)puntero - sizeof(AllocationHeader));
            chunk = (MemoryChunkHeader*)((char*)header - header->bit_index * UNIT_SIZE);


            printf("El puntero es %p\n", puntero);
            printf("El id del chunk es %u\n", chunk->id);
            printf("El total de unidades del chunk es: %u\n", chunk->chunk_total_units);
            printf("Las unidades disponibles en el chunk es: %u\n", chunk->chunk_available_units);
            print_bitmap(chunk->bitmap, chunk->bitmap_size);
        }
        if(option == 2){
            printf("\n--- Quitar Bits ---\n");
            printf("Ingrese el puntero del dato a borrar: ");
            scanf("%p", &puntero_borrar);
            my_free(puntero_borrar);
        }
    }
    return 0;
}