#pragma once
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
