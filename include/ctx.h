#pragma once
#include <stdbool.h>

typedef struct ctx_t {
	// used for error messages and suff
	const char* cmd_name;
	bool verbose;
} ctx_t;
