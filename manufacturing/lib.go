package manufacturing

import (
	"encoding/xml"
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

// implement parsing/saving all of the structs to xml
func (v *Vec2f) UnmarshalXMLAttr(attr xml.Attr) error {
	var parts []string = strings.Fields(attr.Value)
	if len(parts) != 2 {
		return fmt.Errorf("invalid Vec2f: %q", attr.Value)
	}

	var err error
	v.X, err = strconv.ParseFloat(parts[0], 64)
	if err != nil {
		return err
	}
	v.Y, err = strconv.ParseFloat(parts[1], 64)
	return err
}

func (v Vec2f) MarshalXMLAttr(name xml.Name) (xml.Attr, error) {
	val := fmt.Sprintf("%f %f", v.X, v.Y)
	return xml.Attr{Name: name, Value: val}, nil
}

func (v *Vec2f) UnmarshalXML(d *xml.Decoder, start xml.StartElement) error {
	var content string
	if err := d.DecodeElement(&content, &start); err != nil {
		return err
	}

	var parts []string = strings.Fields(content)
	if len(parts) != 2 {
		return fmt.Errorf("invalid Vec2: %q", content)
	}

	var err error
	v.X, err = strconv.ParseFloat(parts[0], 64)
	if err != nil {
		return err
	}
	v.Y, err = strconv.ParseFloat(parts[1], 64)
	return err
}

func (v Vec2f) MarshalXML(e *xml.Encoder, start xml.StartElement) error {
	val := fmt.Sprintf("%f %f", v.X, v.Y)
	return e.EncodeElement(val, start)
}

func (v *Vec2i) UnmarshalXMLAttr(attr xml.Attr) error {
	var parts []string = strings.Fields(attr.Value)
	if len(parts) != 2 {
		return fmt.Errorf("invalid Vec2i: %q", attr.Value)
	}

	var err error
	v.X, err = strconv.ParseInt(parts[0], 10, 64)
	if err != nil {
		return err
	}
	v.Y, err = strconv.ParseInt(parts[1], 10, 64)
	return err
}

func (v Vec2i) MarshalXMLAttr(name xml.Name) (xml.Attr, error) {
	val := fmt.Sprintf("%d %d", v.X, v.Y)
	return xml.Attr{Name: name, Value: val}, nil
}

func (c *Color) UnmarshalXMLAttr(attr xml.Attr) error {
	var parts []string = strings.Fields(attr.Value)
	if len(parts) != 4 && len(parts) != 3 {
		return fmt.Errorf("invalid Color: %q", attr.Value)
	}

	var err error
	c.R, err = strconv.ParseFloat(parts[0], 64)
	if err != nil {
		return err
	}

	c.G, err = strconv.ParseFloat(parts[1], 64)
	if err != nil {
		return err
	}

	c.B, err = strconv.ParseFloat(parts[2], 64)
	if err != nil {
		return err
	}

	// alpha is optional
	if len(parts) == 4 {
		c.A, err = strconv.ParseFloat(parts[1], 64)
	} else {
		c.A = 1
	}

	return err
}

func (c Color) MarshalXMLAttr(name xml.Name) (xml.Attr, error) {
	// @unsure can alpha be used everywhere?
	val := fmt.Sprintf("%f %f %f %f", c.R, c.G, c.B, c.A)
	return xml.Attr{Name: name, Value: val}, nil
}
