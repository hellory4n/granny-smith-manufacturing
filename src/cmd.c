#include <stdio.h>

#include "gsmanufacturing.h"

void cmd_version(void)
{
	printf("granny smith manufacturing v0.0.3\n");
}

void cmd_help(const ctx_t* ctx)
{
	printf("Usage: %s <input svg> <output xml>\n"
	       "\n"
	       "Flags:\n"
	       "    --help, -h:    prints this\n"
	       "    --version, -v: prints the current version\n"
	       "    --verbose:     enables verbose output (for debugging)\n",
	       ctx->cmd_name);
}

void cmd_gen_level(const ctx_t* ctx, const char* input, const char* output)
{
	(void)ctx;
	printf("fuck... from %s to %s\n", input, output);
}
