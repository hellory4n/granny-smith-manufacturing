package manufacturing

import (
	"fmt"
	"strconv"
	"strings"
)

// Tantalizing.
type Vec2f struct {
	X float64
	Y float64
}

// Tantalizing.
type Vec2i struct {
	X int64
	Y int64
}

// Spectacular.
type Vec3f struct {
	X float64
	Y float64
	Z float64
}

// Spectacular.
type Vec3i struct {
	X int64
	Y int64
	Z int64
}

// Extraordinary.
type Vec4f struct {
	X float64
	Y float64
	Z float64
	W float64
}

// Extraordinary.
type Vec4i struct {
	X int64
	Y int64
	Z int64
	W int64
}

// Horrifying.
type Color struct {
	R float64
	G float64
	B float64
	A float64
}

// returns a color from a hexcode in 0xRRGGBBAA format
func Rgba(hex uint32) Color {
	var r uint32 = (hex >> 24) & 0xff
	var g uint32 = (hex >> 16) & 0xff
	var b uint32 = (hex >> 8) & 0xff
	var a uint32 = hex & 0xff
	return Color{float64(r) / 255.0, float64(g) / 255.0, float64(b) / 255.0, float64(a) / 255.0}
}

// returns a color from a hexcode in 0xRRGGBB format
func Rgb(hex uint32) Color {
	var r uint32 = (hex >> 16) & 0xff
	var g uint32 = (hex >> 8) & 0xff
	var b uint32 = hex & 0xff
	return Color{float64(r) / 255.0, float64(g) / 255.0, float64(b) / 255.0, 1}
}

// assertma balls
func Assert(msg string, x bool) {
	if !x {
		panic("failed assert: " + msg)
	}
}

// Go™ fuck yourself
func Must(err error) {
	if err != nil {
		panic(err.Error())
	}
}

func ParseVec2f(str string) (vec Vec2f, err error) {
	var parts []string = strings.Fields(str)
	if len(parts) != 2 {
		return Vec2f{}, fmt.Errorf("invalid Vec2f: %q", str)
	}

	vec.X, err = strconv.ParseFloat(parts[0], 64)
	if err != nil {
		return Vec2f{}, err
	}
	vec.Y, err = strconv.ParseFloat(parts[1], 64)
	return vec, err
}

func (v Vec2f) String() string {
	return fmt.Sprintf("%f %f", v.X, v.Y)
}

func ParseColor(str string) (color Color, err error) {
	var parts []string = strings.Fields(str)
	if len(parts) != 4 && len(parts) != 3 {
		return Color{}, fmt.Errorf("invalid Color: %q", str)
	}

	color.R, err = strconv.ParseFloat(parts[0], 64)
	if err != nil {
		return Color{}, err
	}

	color.G, err = strconv.ParseFloat(parts[1], 64)
	if err != nil {
		return Color{}, err
	}

	color.B, err = strconv.ParseFloat(parts[2], 64)
	if err != nil {
		return Color{}, err
	}

	// alpha is optional
	if len(parts) == 4 {
		color.A, err = strconv.ParseFloat(parts[1], 64)
	} else {
		color.A = 1
	}

	return color, err
}

func (v Color) String() string {
	// FIXME is alpha allowed everywhere?
	return fmt.Sprintf("%f %f %f %f", v.R, v.G, v.B, v.A)
}
