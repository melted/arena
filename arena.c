/* arena.c
 * A simple arena allocator
 *
 * Written by Niklas Larsson (metaniklas@gmail.com)
 *
 * This code is in the public domain, see
 * UNLICENSE for details
 */
#include <stdlib.h>

#include "arena.h"

#define BLOB_MIN 4096
#define CHUNK_SIZE 16384
#define ALIGNMENT 4

struct chunk {
    struct chunk *next;
    void *mem;
    void *current;
    int size;
};

struct blob {
    struct blob *next;
};

struct arena {
    struct chunk *chunks;
    struct blob *blobs;
};

ahandle arena_create(void) 
{
    ahandle a = malloc(sizeof(struct arena));
    a->chunks = NULL;
    a->blobs = NULL;
}

static void create_chunk(ahandle a) 
{
    struct chunk *new_chunk = malloc(sizeof(struct chunk));
    new_chunk->mem = malloc(CHUNK_SIZE);
    new_chunk->current = new_chunk->mem;
    new_chunk->size = CHUNK_SIZE;
    new_chunk->next = a->chunks;
    a->chunks = new_chunk;
}

void *arena_alloc(ahandle a, size_t s) 
{
    void *mem;
    if(s < BLOB_MIN) {
        /* Allocate in a chunk */
        size_t step = s>4?s:4;
        step += ALIGNMENT - (step % ALIGNMENT);
        if(a->chunks == NULL || a->chunks->size < step) {
            create_chunk(a);
        }
        mem = a->chunks->current;
        a->chunks->current+=step;
        a->chunks->size-=step;
    } else {
        /* Allocate a separate blob */
        struct blob* new_blob = malloc(sizeof(struct blob)+s);
        new_blob->next = a->blobs;
        a->blobs = new_blob;
        mem = (void*)new_blob+sizeof(struct blob);
    }
    return mem;
}

void arena_destroy(ahandle a)
{
    struct chunk *ch = a->chunks;
    while(ch) {
        struct chunk *next = ch->next;
        free(ch->mem);
        free(ch);
        ch = next;
    }

    struct blob *bl = a->blobs;
    while(bl) {
        struct blob *next = bl->next;
        free(bl);
        bl = next;
    }

    free(a);
}

