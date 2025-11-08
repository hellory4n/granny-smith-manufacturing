#include "level.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ctx.h"
#include "lib.h"
#define NANOSVG_IMPLEMENTATION
#define NANOSVG_ALL_COLOR_KEYWORDS
#include "nanosvg.h"

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

bool save_level_file(const char* path, const level_file_t* level)
{
	FILE* f = fopen(path, "w");
	if (!f) {
		fprintf(stderr, "couldn't open file '%s'", path);
		return false;
	}

	fprintf(f, "<level");
	// attributes
	fprintf(f, " background=\"%s\"", level->background);
	fprintf(f, " startDelay=\"%f\"", level->start_delay);
	fprintf(f, " startDelayHard=\"%f\"", level->start_delay_hard);
	fprintf(f, " grass=\"%s\"", level->grass);
	fprintf(f, " decals=\"%s\"", level->decals);
	fprintf(f, " badguyspeed=\"%f\"", level->bad_guy_speed);
	fprintf(f, " badguyspeedhard=\"%f\"", level->bad_guy_speed_hard);
	fprintf(f, " gravity=\"%f\"", level->gravity);
	fprintf(f, " bgscrollspeed=\"%f\"", level->background_scroll_speed);
	fprintf(f, " timescale=\"%f\"", level->time_scale);
	fprintf(f, " clearmem=\"%i\"", level->clearmem);
	fprintf(f, " editZoom=\"%f\"", level->edit_zoom);
	fprintf(f, " editPan=\"%f %f\"", level->edit_pan.x, level->edit_pan.y);
	fprintf(f, " editWorkMode=\"%i\"", level->edit_work_mode);
	fprintf(f, ">\n");
	fprintf(f, "  <entities>\n");

	// entities
	for (size_t i = 0; i < level->entity_len; i++) {
		entity_t entity = level->entities[i];
		fprintf(f, "    "); // indentation why not

		switch (entity.type) {
		case ENTITY_TYPE_DUDE: {
			dude_entity_t dude = entity.dude;
			fprintf(f, "<dude");
			fprintf(f, " name=\"%s\"", dude.name);
			fprintf(f, " pos=\"%f %f\"", dude.position.x, dude.position.y);
			fprintf(f, " rot=\"%f\"", dude.rotation);
			fprintf(f, "/>");
		} break;

		case ENTITY_TYPE_BODY: {
			// body entities are fun since there's a billion optional attributes
			body_entity_t body = entity.body;
			fprintf(f, "<body");
			if (body.template.valid) {
				fprintf(f, " template=\"%s\"", body.template.some);
			}
			fprintf(f, " pos=\"%f %f\"", body.position.x, body.position.y);
			fprintf(f, " rot=\"%f\"", body.rotation);
			fprintf(f, " category=\"%i\"", body.category);
			fprintf(f, " color=\"%f %f %f %f\"", body.color.r, body.color.g,
				body.color.b, body.color.a);
			fprintf(f, " z=\"%f\"", body.z);
			fprintf(f, " depth=\"%f\"", body.depth);
			if (body.edge.valid) {
				fprintf(f, " edge=\"%f %f\"", body.edge.some.x, body.edge.some.y);
			}
			if (body.group.valid) {
				fprintf(f, " group=\"%i\"", body.group.some);
			}
			if (body.mapping.valid) {
				fprintf(f, " mapping=\"%s\"", body.mapping.some);
			}
			if (body.curve.valid) {
				fprintf(f, " curve=\"%f %f\"", body.curve.some.x,
					body.curve.some.y);
			}
			if (body.extra_rotation.valid) {
				fprintf(f, " extrarot=\"%f %f %f\"", body.extra_rotation.some.x,
					body.extra_rotation.some.y, body.extra_rotation.some.z);
			}
			if (body.mask.valid) {
				fprintf(f, " mask=\"%i\"", body.mask.some);
			}
			if (body.hidden.valid) {
				fprintf(f, " hidden=\"%i\"", body.hidden.some);
			}
			if (body.surface.valid) {
				fprintf(f, " surface=\"%s\"", body.surface.some);
			}
			fprintf(f, "/>\n");

			// the actual fucking lines shits
			if (body.line_points) {
				fprintf(f, "      <shape>\n");
				for (size_t j = 0; j < body.line_point_len; j++) {
					fprintf(f, "        <v>");
					fprintf(f, "%f %f", body.line_points[j].x,
						body.line_points[j].y);
					fprintf(f, "</v>\n");
				}
				fprintf(f, "      </shape>\n");
			}

			if (body.curve_points) {
				fprintf(f, "      <curve>\n");
				for (size_t j = 0; j < body.curve_point_len; j++) {
					fprintf(f, "        <v>");
					fprintf(f, "%f %f %f %f %f %f", body.curve_points[j][0].x,
						body.curve_points[j][0].y,
						body.curve_points[j][1].x,
						body.curve_points[j][1].y,
						body.curve_points[j][2].x,
						body.curve_points[j][2].y);
					fprintf(f, "</v>\n");
				}
				fprintf(f, "      </curve>\n");
			}

			fprintf(f, "    </body>");
		} break;

		case ENTITY_TYPE_POWERUP: {
			printf("todo\n");
			abort();
		} break;

		case ENTITY_TYPE_BREAKABLE: {
			printf("todo\n");
			abort();
		} break;

		case ENTITY_TYPE_SENSOR: {
			printf("todo\n");
			abort();
		} break;

		case ENTITY_TYPE_JOINT: {
			printf("todo\n");
			abort();
		} break;
		}

		fprintf(f, "\n");
	}

	fprintf(f, "    </entities>\n");
	fprintf(f, "</level>\n");
	fclose(f);
	return true;
}

level_file_t* level_from_svg(ctx_t ctx, arena_t* arena, const char* svg_path)
{
	NSVGimage* svg = nsvgParseFromFile(svg_path, "px", 96);
	if (!svg) {
		fprintf(stderr, "%s: couldn't open '%s'", ctx.cmd_name, svg_path);
		return NULL;
	}

	level_file_t* level = arena_alloc(arena, sizeof(level_file_t));

	return level;
}
