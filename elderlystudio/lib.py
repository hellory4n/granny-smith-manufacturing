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
	x: float
	y: float
	c: float
	"control point"

@dataclass
class CubicBezier:
	x: float
	y: float
	c1: float
	"first control point"
	c2: float
	"second control point"
