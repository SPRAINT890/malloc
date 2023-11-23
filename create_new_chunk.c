#include "my_malloc_manager.h"
MemoryChunkHeader* create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next) {
    void *mem = mmap(NULL, units_needed * UNIT_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (mem == MAP_FAILED) {
        error(EXIT_FAILURE, errno, "Memory mapping failed");
    }

    uint16_t total_units_to_mmap = is_large_allocation ? units_needed + STRUCT_UNITS : units_needed; 
    uint16_t used_units = is_large_allocation? STRUCT_UNITS : STRUCT_UNITS + BITMAP_UNITS;

    MemoryChunkHeader * chunk = (MemoryChunkHeader *)mem;
    chunk->addr = mem;
    chunk->id = id++; //ID único, actualizado según corresponde
    chunk->is_large_allocation = is_large_allocation;
    chunk->chunk_total_units = total_units_to_mmap;
    chunk->chunk_available_units = units_needed - used_units; // Ajustar por el tamaño del encabezado
    chunk->bitmap = is_large_allocation ? 0 : (Bitmap)((char*)(chunk) + STRUCT_UNITS * UNIT_SIZE); // Justo después del encabezado
    chunk->bitmap_size = is_large_allocation ? 0 : BITMAP_SIZE;
    chunk->next = next;

    // Inicializar el bitmap a 0 manualmente
    if(!is_large_allocation){
        set_or_clear_bits(0, chunk->bitmap, 0, 0, units_needed);
        set_or_clear_bits(1, chunk->bitmap, 0, 0, used_units);
    }

    printf("NUEVO CHUNK CREADO, EL ID ES %hd\n", chunk->id);
    return chunk;
}