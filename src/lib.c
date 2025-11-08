#include "lib.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void panic(const char* fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	fprintf(stderr, "panic: ");
	vfprintf(stderr, fmt, arg);
	fprintf(stderr, "\n");
	va_end(arg);
	abort();
}

arena_t arena_new(size_t size)
{
	arena_t arena = { .size = size };
	arena.buffer = calloc(1, size);
	if (arena.buffer == NULL) {
		panic("couldn't allocate arena");
	}
	return arena;
}

void arena_free(arena_t* arena)
{
	free(arena->buffer);
	arena->buffer = NULL;
}

void* arena_alloc(arena_t* arena, size_t size)
{
	// TODO alignment exists
	size_t end = (size_t)arena->alloc_pos + size;
	if (end > arena->size) {
		panic("arena allocation out of bounds");
	}

	void* data = (void*)((uint8_t*)arena->buffer + arena->alloc_pos);
	arena->alloc_pos += size;
	return data;
}
