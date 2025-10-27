// level format, should (mostly) match the xml
// @guess  = fields where i'm not sure what they are
// @unsure = fields where idk small details such as the unit they're using
// @noidea = fields where i have no no idea
// @unused = fields that are in the xml but we don't use (most likely used in mediocre's own editor)

import { Color, Vec2, Vec3 } from "./lib";

/**
 * decalma
 */
export interface Decal {
	name: string;
	coords: [number, number, number, number];
}

/**
 * decalma²
 */
export interface Decals {
	/**
	 * path
	 */
	texture: string;
	decals: Decal[];
}

export interface Level {
	/**
	 * path to the background image
	 */
	background: string;
	/**
	 * @unsure in seconds
	 */
	startDelay: number;
	/**
	 * @unsure in seconds
	 */
	startDelayHard: number;
	/**
	 * path to the ground (?) decal xml
	 */
	grass: string;
	/**
	 * @guess path to more decals i guess?
	 */
	decals: string;
	/**
	 * @unsure as the name implies, the speed of the bad guy aka dude aka thief. idk what the
	 * unit is
	 */
	badGuySpeed: number;
	/**
	 * a bit like `badGuySpeed`, except hard.
	 */
	badGuySpeedHard: number;
	/**
	 * i assume this only exists for the space levels
	 */
	gravity: number;
	/**
	 * @guess parallax or some shit
	 */
	backgroundScrollSpeed: number;
	/**
	 * @noidea
	 */
	timeScale: number;
	/**
	 * @noidea
	 */
	clearmem: number;
	/**
	 * @unused
	 */
	editZoom: number;
	/**
	 * @unused
	 */
	editPan: Vec2;
	/**
	 * @unused
	 */
	editWorkMode: number;
	entities: Entity[];
}

// TODO a lot of fields are shared, use an interface instead of an union
export type Entity = Dude | Body | Powerup | Breakable | Sensor | Joint;

/**
 * aka bad guy aka thief
 */
export interface Dude {
	/**
	 * dude... dude... dude... what? GOOD NEWS GOOD NEWS GOOD NEWS
	 */
	name: string;
	position: Vec2;
	/**
	 * most likely in radians
	 */
	rotation: number;
}

/**
 * @unsure figma curves have 4 points, but the xml has 6, which is still a valid bezier curve. will
 * it accept 4 points or do i have to do some conversion faffery?
 */
export interface CurvePoint {
	p0: number;
	p1: number;
	p2: number;
	p3: number;
	p4: number;
	p5: number;
}

/**
 * land.
 */
export interface Body {
	/**
	 * @noidea might be a prefab type thing?
	 */
	template?: string;
	position: Vec2;
	/**
	 * most likely in radians
	 */
	rotation: number;
	/**
	 * @guess organization thing used by mediocre's editor?
	 */
	category: number;
	color: Color;
	/**
	 * the position's Z axis, which is a different attribute in the xml for some reason
	 */
	z: number;
	/**
	 * individual points don't get to be vec3s, there is only one depth param
	 */
	depth: number;
	/**
	 * probably bevels
	 */
	edge?: Vec2;
	/**
	 * @unused probably
	 */
	group?: number;
	/**
	 * @noidea
	 */
	mapping?: string;
	/**
	 * @noidea i saw somewhere that it was one number, and somewhere else it was 2??
	 */
	curve?: [number, number?];
	/**
	 * extra euler rotation on top of the normal rotation
	 */
	extraRotation?: Vec3;
	/**
	 * @noidea
	 */
	mask?: number;
	/**
	 * null = false = visible
	 */
	hidden?: boolean;
	/**
	 * @noidea
	 */
	surface?: string;
	// some fields might be missing since there's a lot of optional fields
	// @noidea textures were too weird to include here just yet
	/**
	 * @unsure body entities seem to always either have lines or curves but never both, is that an engine limitation or just the way that mediocre's editor was used?
	 */
	points: (Vec2 | CurvePoint)[];
}

/**
 * powerupma
 */
export interface Powerup {
	position: Vec2;
	rotation: number;
	/**
	 * @unsure what are the other types?
	 */
	type?: "apple";
}

/**
 * granny falls into glass and dies
 */
export interface Breakable {
	position: Vec2;
	rotation: number;
	/**
	 * @unsure what is the default type?
	 */
	type?: "metal";
	/**
	 * path.
	 */
	texture: string;
	/**
	 * @noidea
	 */
	texScale: Vec2;
	/**
	 * @noidea
	 */
	texOffset: Vec2;
	color: Color;
	width: number;
	height: number;
	/**
	 * @guess maybe you lose health if you break it or some shit
	 */
	penalty?: number;
	/**
	 * @unused probably
	 */
	group?: number;
}

export interface Sensor {
	name?: string;
	position: Vec2;
	rotation: number;
	type?: "box";
	/**
	 * @unsure sometimes there's only 1 number
	 */
	size: Vec2;
	/**
	 * @unsure this one seems a bit complicated
	 */
	action: string;
	/**
	 * @unused probably
	 */
	group?: number;
}

/**
 * @guess physics thing?
 */
export interface Joint {
	/**
	 * @guess prefab thing?
	 */
	template?: string;
	position: Vec2;
	rotation: number;
	/**
	 * @unused probably
	 */
	group?: number;
	/**
	 * @noidea might be a bool
	 */
	fixed: number;
	/**
	 * position's Z axis
	 */
	z?: number;
}

export function loadDecal(_path: string): Decals {
	throw "TODO";
}

export function saveDecal(_decal: Decals, _path: string): void {
	throw "TODO";
}

export function loadLevel(_path: string): Level {
	throw "TODO";
}

export function saveLevel(_level: Level, _path: string): void {
	throw "TODO";
}
