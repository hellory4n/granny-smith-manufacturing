#include "level.h"

#include <stddef.h>
#include <stdio.h>

bool save_decal_file(const char* path, const decal_file_t* decal)
{
	FILE* f = fopen(path, "w");
	if (!f) {
		fprintf(stderr, "couldn't open file '%s'", path);
		return false;
	}

	fprintf(f, "<decals texture=\"%s\">\n", decal->texture);

	for (size_t i = 0; i < decal->decal_len; i++) {
		decal_t item = decal->decals[i];
		fprintf(f, "    <decal name=\"%s\" coords=\"%.0f %.0f %.0f %.0f\"/>\n", item.name,
			item.coords.x, item.coords.y, item.coords.z, item.coords.w);
	}

	fprintf(f, "</decals>\n");
	fclose(f);
	return true;
}
