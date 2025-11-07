package manufacturing

import "encoding/xml"

// level format, should (mostly) match the xml
// @guess  = fields where i'm not sure what they are
// @unsure = fields where idk small details such as the unit they're using
// @noidea = fields where i have no no idea
// @unused = fields that are in the xml but we don't use (most likely used in mediocre's own editor)
// xml tags are used for documentation but we don't use go's marshal functions which use reflection
// faffery to parse everything

// decalma
type Decal struct {
	XMLName xml.Name `xml:"decal"`
	Name    string   `xml:"name,attr"`
	Coords  Vec4f    `xml:"coords,attr"`
}

type DecalFile struct {
	XMLName xml.Name `xml:"decals"`
	// path
	Texture string  `xml:"texture,attr"`
	Decals  []Decal `xml:"decal"`
}

type LevelFile struct {
	XMLName xml.Name `xml:"level"`
	// path to a texture
	Background string `xml:"background,attr"`
	// in seconds
	StartDelay     float64 `xml:"startDelay,attr"`
	StartDelayHard float64 `xml:"startDelayHard,attr"`
	// @unsure path to the ground (?) decal xml
	GrassDecal string `xml:"grass,attr"`
	// path to more decals that can be used with the <decal> entity
	Decals string `xml:"decals,attr"`
	// @unsure as the name implies, the speed of the bad guy aka dude aka thief. idk what the
	// unit is
	BadGuySpeed float64 `xml:"badguyspeed,attr"`
	// a bit like `BadGuySpeed`, except hard.
	BadGuySpeedHard float64 `xml:"badguyspeedhard,attr"`
	// i assume this only exists for the space levels
	Gravity float64 `xml:"gravity,attr"`
	// @guess parallax or some shit
	BackgroundScrollSpeed float64 `xml:"bgscrollspeed,attr"`
	// @noidea
	TimeScale float64 `xml:"timescale,attr"`
	// @noidea
	ClearMem int32 `xml:"clearmem,attr"`
	// @unused
	EditZoom float64 `xml:"editZoom,attr"`
	// @unused
	EditPan Vec2f `xml:"editPan,attr"`
	// @unused
	EditWorkMode Vec2f `xml:"editWorkMode,attr"`
}

// @unsure figma curves have 4 points, but the xml has 6, which is still a valid bezier curve.
// will it accept 4 points or do i have to do some conversion faffery?
type CurvePoint struct {
	p0 float64
	p1 float64
	p2 float64
	p3 float64
	p4 float64
	p5 float64
}

// STOP using ANTI-GO language
// wrong: go's type system is dogwater
// right: GO KNOWS BEST
type Entity any

type DudeEntity struct {
	XMLName  xml.Name `xml:"dude"`
	Name     string   `xml:"dude,attr"`
	Position Vec2f    `xml:"pos,attr"`
	// most likely in radians
	Rotation float64 `xml:"rot,attr"`
}
