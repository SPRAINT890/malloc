#include "my_malloc_manager.h"
void my_malloc_init(){
    first_chunk = create_new_chunk(UNITS_PER_CHUNK, 0, NULL);

}

void *my_malloc(size_t nbytes){
    // allocates nbytes bytes and returns a pointer to the allocated memory
    // Calculate the number of units needed
    // Always add the size in units of the allocated memory at the beginning, using sizeof (AllocationHeader) bytes for it
    
    uint16_t units_needed = (nbytes + sizeof(AllocationHeader) + UNIT_SIZE - 1) / UNIT_SIZE;

    MemoryChunkHeader *chunk = NULL;

    int bit_index;
    int is_large_allocation = IS_LARGE_ALLOCATION(units_needed);

    if (first_chunk == NULL) {
        my_malloc_init(); // \nitialize the memory manager
    }

    for (chunk = first_chunk; chunk != NULL; chunk = chunk->next) {
        // Attempt to find the first fit in the bitmap
        printf("unidades necesitadas %hd. \n", units_needed);
        printf("Se esta buscando en el chunk id %hd. \n", chunk->id);
        
        if (units_needed > chunk->chunk_available_units) {// if the chunk is for large allocation it will have 0 available units too
            printf("No hay suficiente espacion en el chunk %hd este tiene %hd unidades libres\n", chunk->id, chunk->chunk_available_units);
            continue; // go to next chunk
        }
        bit_index = first_fit(chunk->bitmap, chunk->bitmap_size, units_needed);
        if (bit_index == -1) {
            printf("No hay suficiente espacio en el chunk %hd\n", chunk->id);
        } else {// found!
            printf("Se encontro un espacio en el bit index %d\n", bit_index);
        }
        
        if (chunk == NULL) {// have to create a new standard chunk, and will insert it right after the first chunk
        printf("\nSe necesita crear un nuevo chunk estandar. se necesita %hd units. \n", units_needed);
        chunk = first_chunk->next = create_new_chunk (units_needed, 0, first_chunk->next); // 0 means FALSE is_large_allocation
        bit_index = first_fit(chunk->bitmap, chunk->bitmap_size, units_needed);
            if (bit_index == -1) { // should never happen
                printf("Not enough space for first fit in chunk id %u hd\n", chunk->id);
                // error (EXIT_FAILURE, 0, "bit index return -1 on new chunk, programming error. Exiting.");
            }
        }
    }
    printf("\nSe encontro un hueco en %hd en el bit index %d\n", first_chunk->id, bit_index);
    first_chunk->chunk_available_units -= units_needed;
    size_t offset = bit_index * UNIT_SIZE;
    AllocationHeader *allocation_header = (AllocationHeader *) ((char *) first_chunk->addr + offset);
    allocation_header->nunits = units_needed;
    allocation_header->bit_index = bit_index;
    return (char *) allocation_header + sizeof (AllocationHeader);
}
