/*
 * example.c
 * A silly example for the arena allocator
 *
 * Written by Niklas Larsson (metaniklas@gmail.com)
 *
 * This code is in the public domain, see
 * UNLICENSE for details
 */

#include <stdio.h>
#include "arena.h"

int main(int argc, char **argv)
{
    ahandle arena = arena_create();
    int i;
    for(i = 0; i<10000; i++) {
        /* something small */
        char *n = arena_alloc(arena, 1000);
        /* and something large */
        char *m = arena_alloc(arena, 100000);
    }
    arena_destroy(arena);
    printf("I deleted everything, honest. Run me under Valgrind if you don't believe me!\n");
    return 0;
}
