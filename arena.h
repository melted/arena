/*
 * Arena.h
 * A simple arena allocator
 *
 * Written by Niklas Larsson (metaniklas@gmail.com)
 *
 * This code is in the public domain, see
 * UNLICENSE for details
 */

#ifndef ARENA_H
#define ARENA_H
struct arena;

typedef struct arena *ahandle;


ahandle arena_create(void);

void *arena_alloc(ahandle a, size_t s);

void arena_destroy(ahandle a);

#endif
