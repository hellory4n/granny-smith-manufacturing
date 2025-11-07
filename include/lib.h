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

#define streql(a, b) (strcmp(a, b) == 0)
// i'm not gonna use heap memory for random optional fields
#define OPTIONAL(type)                                                                             \
	struct {                                                                                   \
		bool valid;                                                                        \
		union {                                                                            \
			type some;                                                                 \
			unsigned char none;                                                        \
		};                                                                                 \
	}
