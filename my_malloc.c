#include "my_malloc_manager.h"

void* my_malloc_init(){
    MemoryChunkHeader* chunk_cero = create_new_chunk(UNITS_PER_CHUNK, 0, NULL);
}

void *my_malloc(size_t nbytes, MemoryChunkHeader* chunk_cero){
    uint16_t unidades_requeridas = (nbytes + sizeof(AllocationHeader) + UNIT_SIZE -1) / UNIT_SIZE;
    MemoryChunkHeader *chunk = NULL;
    int bit_index;
    int is_large_allocation = IS_LARGE_ALLOCATION(unidades_requeridas);
    
    if (chunk_cero == NULL){
        my_malloc_init();
    }

    for (chunk = chunk_cero; chunk != NULL; chunk = chunk -> next) {
        printf("Unidades requeridas %hd. \n", unidades_requeridas);
        printf("Se buscaran en el chunk %hd. \n", chunk->id);
    }

    if (unidades_requeridas > chunk ->chunk_available_units){
        printf("No hay espacio suficiente en el chunk %hd que tiene %hd unidads libres\n", chunk ->id, chunk ->chunk_available_units);
        return -1;
    }
    
    bit_index = first_fit(chunk->bitmap, chunk->bitmap_size, unidades_requeridas);
    if (bit_index == -1) {
        printf("No hay espacio suficiente para el first fit en el chunk %hd \n", chunk -> id);
    } else {
        return -1;
    }

}
/*
if (chunk == NULL){
    printf("\n Nuevo chunk para alocación estandar se creara. Se necesitan %hd unidades. \n", units_needed);
    bit_index = first_fit(chunk -> bitmap, chunk -> bitmap_size, unidades_requeridas);
    bit_index = first_fit(chunk->bitmap, chunk->bitmap_size, units_needed);
    if (bit_index == -1){
        printf("No hay espacio suficiente para el first fit en el chunk %hd \n", chunk -> id);
    }
    printf("\n Se encontró un espacio en el chunk %hd en el bit %d \n", chunk -> id, bit_index);
}
chunk -> chunk_unidades_disponibles -= unidades_requeridas;
size_t offset = bit_index + UNITS_SIZE;
AllocationHeader *allocation_header = (AllocationHeader *) ((char *) chunk->addr + offset);
allocation_header -> bit_index = bit_index;

return (char *) allocation_header + sizeof (AllocationHeader);
*/