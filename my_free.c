#include "my_malloc_manager.h"

void my_free(void *ptr) {
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
    
    if (!chunk) {
        fprintf(stderr, "Invalid pointer passed to my_free.\n");
        exit(EXIT_FAILURE);
    }

    chunk->chunk_available_units += units;
    uint16_t byte = header->bit_index / 8;
    uint16_t bit = header->bit_index % 8;

    if (!chunk->is_large_allocation){
        set_or_clear_bits(0, chunk->bitmap, byte, bit, units);
    }else{
        int id = chunk->id;
        MemoryChunkHeader *temp = first_chunk;
        while (temp->next->id != id){
            temp = temp->next;
        }
        temp->next = chunk->next;
    }
    printf("\n");
    print_varius_bitmap(first_chunk);
    printf("Freeing %d units from chunk %p\n", units, chunk);
}