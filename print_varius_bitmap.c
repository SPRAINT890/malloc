#include "my_malloc_manager.h"

void print_varius_bitmap(MemoryChunkHeader* chunk){
    while (chunk != NULL){
        printf("\nChunk %hd\n", chunk->id);
        print_bitmap(chunk->bitmap, chunk->bitmap_size);
        chunk = chunk->next;
    }
    return;
}