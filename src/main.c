#include <assert.h>
#include <stdio.h>

#include "ctx.h"
#include "gsmanufacturing.h"
#include "level.h"
#include "lib.h"

int main(int argc, char* argv[])
{
	arena_t arena = arena_new(1024 * 32);
	decal_file_t decalma = {
		.texture = "balls.png",
	};
	decalma.decals = arena_alloc(&arena, sizeof(decal_t) * 3);
	decalma.decals[0] = (decal_t) {
		.name = "decalma",
		.coords = { { 1, 2, 3, 4 } },
	};
	decalma.decals[1] = (decal_t) {
		.name = "it was the night we had to fart",
		.coords = { { 4, 3, 2, 1 } },
	};
	decalma.decals[2] = (decal_t) {
		.name = "the the uhh um",
		.coords = { { 32175472, 3, 0, 1 } },
	};
	decalma.decal_len = 3;
	save_decal_file("man.xml", &decalma);
	arena_free(&arena);

	assert(argc > 0); // first arg must be the exe name
	ctx_t ctx = {
		.cmd_name = argv[0],
		.verbose = false,
	};

	// TODO gui for the technologically impaired
	if (argc <= 1) {
		cmd_help(&ctx);
		return 0;
	}

	const char* output = "";
	const char* input = "";

	// janky arg parsing
	for (int i = 1; i < argc; i++) {
		const char* arg = argv[i];

		if (streql(arg, "-h") || streql(arg, "--help") || streql(arg, "help")) {
			cmd_help(&ctx);
			return 0;
		}
		else if (streql(arg, "-v") || streql(arg, "--version") || streql(arg, "version")) {
			cmd_version();
			return 0;
		}
		else if (streql(arg, "--verbose")) {
			ctx.verbose = true;
		}
		// first arg is the input, second arg is the output
		else {
			if (strlen(input) != 0 && strlen(output) != 0) {
				printf("%s: there can only be one input file\n", argv[0]);
				return 1;
			}

			if (strlen(input) == 0) {
				input = arg;
			}
			else {
				output = arg;
			}
		}
	}

	if (strlen(input) == 0 || strlen(output) == 0) {
		cmd_help(&ctx);
		return 0;
	}

	cmd_gen_level(&ctx, input, output);
	return 0;
}
