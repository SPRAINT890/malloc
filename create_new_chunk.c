#include "my_malloc_manager.h"
void* create_new_chunk(uint16_t units_needed, int is_large_allocation, MemoryChunkHeader *next) {
    // Calculate the total size needed for the new chunk
    size_t total_size_in_bytes = UNIT_SIZE * UNITS_PER_CHUNK;

    // Allocate memory for the new chunk
    MemoryChunkHeader* new_chunk = mmap(NULL, total_size_in_bytes, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (new_chunk == MAP_FAILED) {
        error(EXIT_FAILURE, errno, "Memory mapping failed");
    }

    // Initialize the memory chunk header
    new_chunk->id = 0;  // Set an appropriate ID or leave it as 0
    new_chunk->is_large_allocation = is_large_allocation;
    new_chunk->chunk_total_units = UNITS_PER_CHUNK;
    new_chunk->chunk_available_units = units_needed; // Initially, all units are available
    new_chunk->bitmap = (Bitmap) new_chunk+STRUCT_UNITS;  // Set to the appropriate value based on your logic
    new_chunk->bitmap_size = BITMAP_SIZE;  // Set to the appropriate value based on your logic
    new_chunk->next = next;

    free_bits(new_chunk->bitmap, new_chunk->bitmap_size, new_chunk->chunk_total_units, 0);
    // Return a pointer to the allocated memory region after the header
    return new_chunk;
}