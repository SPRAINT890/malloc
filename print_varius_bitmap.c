#include "my_malloc_manager.h"

void print_varius_bitmap(MemoryChunkHeader* chunk){
    while (chunk != NULL){
        if (chunk->is_large_allocation == 1){
            printf("\nChunk %hd, Es una alocacion larga\n", chunk->id);
            chunk = chunk->next;
            continue;
        }
        
        printf("\nChunk %hd\n", chunk->id);
        print_bitmap(chunk->bitmap, chunk->bitmap_size);
        chunk = chunk->next;
    }
    return;
}