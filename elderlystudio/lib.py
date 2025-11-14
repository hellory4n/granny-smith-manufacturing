from dataclasses import dataclass

@dataclass
class Vec2f:
	x: float
	y: float

@dataclass
class Vec3f:
	x: float
	y: float
	z: float

@dataclass
class Vec4f:
	x: float
	y: float
	z: float
	w: float

@dataclass
class Vec2i:
	x: int
	y: int

@dataclass
class Vec3i:
	x: int
	y: int
	z: int

@dataclass
class Vec4i:
	x: int
	y: int
	z: int
	w: int

@dataclass
class QuadraticBezier:
	x1: float
	y1: float
	c1: float
	"control point"

	x2: float
	y2: float
	c2: float
	"control point"

@dataclass
class CubicBezier:
	x1: float
	y1: float
	c1: float
	"first control point"
	d1: float
	"second control point"

	x2: float
	y2: float
	c2: float
	"first control point"
	d2: float
	"second control point"
