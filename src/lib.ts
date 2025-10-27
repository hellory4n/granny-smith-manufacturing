// Tantalizing.
export class Vec2 {
	constructor(
		public x: number,
		public y: number,
	) {}
}

// Spectacular.
export class Vec3 {
	constructor(
		public x: number,
		public y: number,
		public z: number,
	) {}
}

export class Color {
	constructor(
		public r: number,
		public g: number,
		public b: number,
		public a: number = 1,
	) {}
}

/**
 * returns a color from a hexcode in 0xRRGGBBAA format
 */
export function rgba(hex: number): Color {
	const r = (hex >> 24) & 0xff;
	const g = (hex >> 16) & 0xff;
	const b = (hex >> 8) & 0xff;
	const a = hex & 0xff;
	return new Color(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
}

/**
 * returns a color from a hexcode in 0xRRGGBB format
 */
export function rgb(hex: number): Color {
	const r = (hex >> 16) & 0xff;
	const g = (hex >> 8) & 0xff;
	const b = hex & 0xff;
	return new Color(r / 255.0, g / 255.0, b / 255.0, 1.0);
}
