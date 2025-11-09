#pragma once
// level format, should (mostly) match the xml
// @guess  = fields where i'm not sure what they are
// @unsure = fields where idk small details such as the unit they're using
// @noidea = fields where i have no no idea
// @unused = fields that are in the xml but we don't use (most likely used in mediocre's own editor)

#include "ctx.h"
#include "lib.h"

// this is horrible alignment but i don't care
// all rotations are in radians
// positions use opengl-style coordinates

// decalma
typedef struct decal_t {
	const char* name;
	vec4_t coords;
} decal_t;

// decalma²
typedef struct decal_file_t {
	// path
	const char* texture;
	decal_t* decals;
	size_t decal_len;
} decal_file_t;

typedef struct dude_entity_t {
	// dude... dude... dude... what? GOOD NEWS GOOD NEWS GOOD NEWS
	const char* name;
	vec2_t position;
	double rotation;
} dude_entity_t;

// land.
typedef struct body_entity_t {
	// @guess might be a prefab type thing?
	OPTIONAL(const char*) template;
	vec2_t position;
	// most likely in radians
	double rotation;
	// @guess organization thing used by mediocre's editor?
	int category;
	vec4_t color;
	// the position's Z axis, which is a different attribute in the xml for some reason
	double z;
	// individual points don't get to be vec3s, there is only one depth param
	double depth;
	// probably bevels
	OPTIONAL(vec2_t) edge;
	// @unused probably
	OPTIONAL(int) group;
	// @noidea
	OPTIONAL(const char*) mapping;
	// @noidea i saw somewhere that it was one number, and somewhere else it was 2??
	OPTIONAL(vec2_t) curve;
	// extra euler rotation on top of the normal rotation
	OPTIONAL(vec3_t) extra_rotation;
	// @noidea
	OPTIONAL(int) mask;
	// null = false = visible
	OPTIONAL(bool) hidden;
	// - 'roll' makes granny turn to be on her feet when she lands on the terrain
	// - 'slip' disables granny from landing on the terrain or getting hurt from smacking into
	//   it
	// - @unsure 'metal roll' might change the material type to metal
	OPTIONAL(const char*) surface;

	// some attributes might be missing since there's a lot of optional fields
	// @noidea textures were too weird to include here just yet

	vec2_t* line_points;
	size_t line_point_len;
	quadratic_bezier_t* curve_points;
	size_t curve_point_len;
} body_entity_t;

// powerupma
typedef struct powerup_entity_t {
	vec2_t position;
	double rotation;
	// @unsure what are the other types? the ones i know:
	// - 'apple'
	const char* type;
} powerup_entity_t;

// granny falls into glass and dies
typedef struct breakable_entity_t {
	vec2_t position;
	double rotation;
	// @unsure what are the other types? the ones i know:
	// - 'metal'
	OPTIONAL(const char*) type;
	// path
	const char* texture;
	// @noidea
	vec2_t tex_scale;
	// @noidea
	vec2_t tex_offset;
	vec4_t color;
	double width;
	double height;
	// @guess maybe you lose health if you break it or some shit
	OPTIONAL(double) penalty;
	// @unused probably
	OPTIONAL(int) group;
} breakable_entity_t;

typedef struct sensor_entity_t {
	OPTIONAL(const char*) name;
	vec2_t position;
	double rotation;
	// @unsure what are the other types? the ones i know:
	// - 'box'
	OPTIONAL(const char*) type;
	// @unsure sometimes there's only 1 number
	vec2_t size;
	// @unsure seems complicated (should be its own struct)
	const char* action;
	// @unused probably
	int group;
} sensor_entity_t;

// @guess physics thing?
typedef struct joint_entity_t {
	// @guess prefab thing?
	OPTIONAL(const char*) template;
	vec2_t position;
	double rotation;
	// @unused probably
	OPTIONAL(int) group;
	// @noidea might be a bool
	int fixed;
	// position's Z axis
	OPTIONAL(double) z;
} joint_entity_t;

typedef enum entity_type_t {
	ENTITY_TYPE_DUDE,
	ENTITY_TYPE_BODY,
	ENTITY_TYPE_POWERUP,
	ENTITY_TYPE_BREAKABLE,
	ENTITY_TYPE_SENSOR,
	ENTITY_TYPE_JOINT,
} entity_type_t;

typedef struct entity_t {
	entity_type_t type;
	union {
		dude_entity_t dude;
		body_entity_t body;
		powerup_entity_t powerup;
		breakable_entity_t breakable;
		sensor_entity_t sensor;
		joint_entity_t joint;
	};
} entity_t;

typedef struct level_file_t {
	// path to the background image
	const char* background;
	// in seconds
	double start_delay;
	// in seconds
	double start_delay_hard;
	// path to the ground (?) decal xml
	const char* grass;
	// path to a decal file with more decals
	const char* decals;
	// as the name implies, the speed of the bad guy aka dude aka thief. idk what the unit is
	double bad_guy_speed;
	// a bit like 'bad_guy_speed', except hard.
	double bad_guy_speed_hard;
	// i assume this only exists for the space levels
	double gravity;
	// @guess parallax or some shit
	double background_scroll_speed;
	// @noidea
	double time_scale;
	// @noidea
	int clearmem;
	// @unused
	double edit_zoom;
	// @unused
	vec2_t edit_pan;
	// @unused
	int edit_work_mode;

	entity_t* entities;
	size_t entity_len;
} level_file_t;

// returns true on success, false on failure
bool save_decal_file(const char* path, const decal_file_t* decal);

// returns true on success, false on failure
bool save_level_file(const char* path, const level_file_t* level);

// parses an svg file and makes a level struct from that. returns null on failure
level_file_t* level_from_svg(ctx_t ctx, arena_t* arena, const char* svg_path);
