#include "my_malloc_manager.h"

void my_free(void *ptr, int id_a_borrar) {
    if (ptr == NULL) {
        return;
    }
    // Obtenga el encabezado de la asignación 
    AllocationHeader *header = (AllocationHeader *)(((char *)ptr) - sizeof(AllocationHeader));
    // Obtener el encabezado del bloque de memoria
    MemoryChunkHeader *chunk = (MemoryChunkHeader *)(((char *)header) - header->bit_index * UNIT_SIZE);
    // Obtenemos el número de unidades de la asignación
    uint16_t units = header->nunits;
    // Actualiza las unidades disponibles en el chunk

    while (chunk != NULL){
        if(chunk->id == id_a_borrar){ 
            printf("\n\n\nEncontre el chunk\n\n");
            break;
        }
        chunk = chunk->next;
    }

    if (chunk->is_large_allocation == 1){
        MemoryChunkHeader *chunk2 = first_chunk;
        MemoryChunkHeader *temp;
        while (chunk2 != NULL){
            temp = chunk2->next;
            if(temp->id == id_a_borrar){
                chunk2->next = temp->next;
                print_varius_bitmap(first_chunk);
                return;
            }
        }
    }
    
    chunk->chunk_available_units += units;
    if (!chunk) {
        fprintf(stderr, "Invalid pointer passed to my_free.\n");
        exit(EXIT_FAILURE);
    }
    
    uint16_t byte = header->bit_index / 8;
    uint16_t bit = header->bit_index % 8;
    set_or_clear_bits(0, chunk->bitmap, byte, bit, units);
    printf("\n");
    print_varius_bitmap(first_chunk);
    printf("Freeing %d units from chunk %p\n", units, chunk);
}