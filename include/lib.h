#pragma once
#include <stdbool.h> // IWYU pragma: export
#include <stddef.h> // IWYU pragma: export
#include <stdint.h> // IWYU pragma: export
#include <string.h> // IWYU pragma: export

typedef struct vec2_t {
	float x;
	float y;
} vec2_t;

typedef union vec3_t {
	struct {
		float x, y, z;
	};
	struct {
		float r, g, b;
	};
} vec3_t;

typedef union vec4_t {
	struct {
		float x, y, z, w;
	};
	struct {
		float r, g, b, a;
	};
} vec4_t;

// curves everyone uses
typedef vec2_t cubic_bezier_t[4];
// curves granny smith uses for whatever reason
typedef vec2_t quadratic_bezier_t[3];

#define streql(a, b) (strcmp(a, b) == 0)
// i'm not gonna use heap memory for random optional fields
#define OPTIONAL(type)                      \
	struct {                            \
		bool valid;                 \
		union {                     \
			type some;          \
			unsigned char none; \
		};                          \
	}

// Oh god oh fuck.
void panic(const char* fmt, ...);

// arena stolen from very early libtrippin
// since that's easier than porting C++ code
typedef struct {
	size_t size;
	size_t alloc_pos;
	void* buffer;
} arena_t;

// Makes a new arena :)
arena_t arena_new(size_t size);

// Frees the arena and everything inside it.
void arena_free(arena_t* arena);

// Allocates space in the arena.
void* arena_alloc(arena_t* arena, size_t size);
