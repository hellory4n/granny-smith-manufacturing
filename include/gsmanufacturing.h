#pragma once
#include "ctx.h"

// commands
void cmd_version(void);
void cmd_help(const ctx_t* ctx);
void cmd_gen_level(const ctx_t* ctx, const char* input, const char* output);
