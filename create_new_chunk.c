#include "my_malloc_manager.h"
MemoryChunkHeader* create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next) {
    size_t total_size = UNITS_PER_CHUNK;

    void *mem = mmap(NULL, units_needed * UNIT_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (mem == MAP_FAILED) {
        error(EXIT_FAILURE, errno, "Memory mapping failed");
    }
    uint16_t used_units = STRUCT_UNITS + BITMAP_UNITS;

    MemoryChunkHeader * chunk = (MemoryChunkHeader *)mem;
    chunk->addr = mem;
    chunk->id = id++; //ID único, actualizado según corresponde
    chunk->is_large_allocation = is_large_allocation;
    chunk->chunk_total_units = units_needed;
    chunk->chunk_available_units = units_needed - (sizeof(MemoryChunkHeader) * 8 / UNIT_SIZE); // Ajustar por el tamaño del encabezado
    chunk->bitmap = (Bitmap)(chunk + 1); // Justo después del encabezado
    chunk->bitmap_size = BITMAP_SIZE;
    chunk->next = next;

    // Inicializar el bitmap a 0 manualmente
    if(!is_large_allocation){
        set_or_clear_bits(1, chunk->bitmap, 0, 0, STRUCT_UNITS + ((sizeof(BITMAP_SIZE) + UNIT_SIZE - 1) / UNIT_SIZE));
    }

    printf("New chunk created, BITMAP pointer: %p\n", chunk->bitmap);
    return chunk;
}