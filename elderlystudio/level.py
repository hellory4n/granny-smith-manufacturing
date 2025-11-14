# level format, should (mostly) match the xml
# @guess  = fields where i'm not sure what they are
# @unsure = fields where idk small details such as the unit they're using
# @noidea = fields where i have no no idea
# @unused = fields that are in the xml but we don't use (most likely used in mediocre's own editor)
# positions use opengl-style coordinates
# rotations are in radians

from dataclasses import dataclass
from typing import cast
from .lib import QuadraticBezier, Vec2f, Vec3f, Vec4i, Vec4f

@dataclass
class Decal:
	"""Not to be confused with DecalEntity, this one just specifies coords on a texture"""
	name: str
	coords: Vec4i

@dataclass
class DecalFile:
	"""decalma"""

	texture: str
	"path"

	decals: list[Decal]

@dataclass
class DudeEntity:
	"""dude... dude... dude... what? GOOD NEWS GOOD NEWS GOOD NEWS"""
	name: str
	position: Vec2f
	rotation: float

@dataclass
class BodyEntity:
	"""land."""

	template: str | None
	"@guess might be a prefab type thing?"

	position: Vec2f
	rotation: float

	category: int
	"@guess organization thing used by mediocre's editor?"

	color: Vec4f

	z: float
	"the position's Z axis, which is a different attribute in the xml for some reason"

	depth: float
	"individual points don't get to be vec3s, there is only one depth param"

	edge: Vec2f | None
	"probably bevels"

	group: int | None
	"@unused probably"

	mapping: str | None
	"@noidea"

	curve: Vec2f | None
	"@noidea i saw somewhere that it was one number, and somewhere else it was 2??"

	extra_rotation: Vec3f | None
	"extra euler rotation on top of the normal rotation"

	mask: int | None
	"@noidea"

	hidden: bool | None
	"null = false = visible"

	surface: str | None
	"""
	- 'roll' makes granny turn to be on her feet when she lands on the terrain
	- 'slip' disables granny from landing on the terrain or getting hurt from smacking into it
	- @unsure 'metal roll' might change the material type to metal
	"""

	# some attributes might be missing since there's a lot of optional fields
	# @noidea textures were too weird to include here just yet

	points: list[QuadraticBezier]
	"lines are just treated as a curiously straight curve"

@dataclass
class PowerupEntity:
	"powerupma"

	position: Vec2f
	rotation: float
	type: str
	"""
	@unsure what are the other types? the ones i know:
	- 'apple'
	"""

@dataclass
class BreakableEntity:
	"""granny falls into glass and dies"""

	position: Vec2f
	rotation: float
	type: str | None
	"""
	@unsure what are the other types? the ones i know:
	- 'metal'
	"""

	texture: str
	"path"

	tex_scale: Vec2f
	"@noidea"

	tex_offset: Vec2f
	"@noidea"

	color: Vec4f
	width: float
	height: float

	penalty: float | None
	"@guess maybe you lose health if you break it or some shit"

	group: int | None
	"@unused probably"

@dataclass
class SensorEntity:
	"""does shit when shit hapens. fascinatg . """

	name: str | None
	position: Vec2f
	rotation: float
	type: str | None
	"""
	@unsure what are the other types? the ones i know:
	- 'box'
	"""

	size: Vec2f
	"@unsure sometimes there's only 1 number"

	action: str
	"@unsure seems complicated (should be its own struct)"

	group: int
	"@unused probably"

@dataclass
class JointEntity:
	"""@guess physics thing?"""

	template: str | None
	"@guess prefab thing?"

	position: Vec2f
	rotation: float

	group: int | None
	"@unused probably"

	fixed: int | None
	"@noidea might be a bool"

	z: float | None
	"position's Z axis"

type Entity = DudeEntity | BodyEntity | PowerupEntity | BreakableEntity | SensorEntity | JointEntity
" entitye"

@dataclass
class LevelFile:
	"""LEvelmz a"""

	background: str
	"path to the background image"

	start_delay: float
	"in seconds"

	start_delay_hard: float
	"in seconds"

	grass: str
	"path to the ground (?) decal xml"

	decals: str
	"path to a decal file with more decals"

	bad_guy_speed: float
	"as the name implies, the speed of the bad guy aka dude aka thief. idk what the unit is"

	bad_guy_speed_hard: float
	"a bit like 'bad_guy_speed', except hard."

	gravity: float
	"i assume this only exists for the space levels"

	background_scroll_speed: float
	"@guess parallax or some shit"

	time_scale: float
	"@noidea"

	clearmem: int
	"@noidea"

	edit_zoom: float
	"@unusesd"

	edit_pan: Vec2f
	"@unused"

	edit_work_mode: int
	"@unused"

	entities: list[Entity]

def save_decal_file(path: str, decal: DecalFile) -> None:
	with open(path, "w") as f:
		f.write(f'<decals texture="{decal.texture}">')

		for decalm in decal.decals:
			f.write(f'<decal name="{decalm.name}" coords="{decalm.coords.x} {decalm.coords.y} {decalm.coords.z} {decalm.coords.w}">')

		f.write("</decals>")
		f.write("\n")

def save_level_file(path: str, level: LevelFile) -> None:
	with open(path, "w") as f:
		f.write("<level")
		# attributes
		f.write(f' background="{level.background}"')
		f.write(f' startDelay="{level.start_delay}"')
		f.write(f' startDelayHard="{level.start_delay_hard}"')
		f.write(f' grass="{level.grass}"')
		f.write(f' decals="{level.decals}"')
		f.write(f' badguyspeed="{level.bad_guy_speed}"')
		f.write(f' badguyspeedhard="{level.bad_guy_speed_hard}"')
		f.write(f' gravity="{level.gravity}"')
		f.write(f' bgscrollspeed="{level.background_scroll_speed}"')
		f.write(f' timescale="{level.time_scale}"')
		f.write(f' clearmem="{level.clearmem}"')
		f.write(f' editZoom="{level.edit_zoom}"')
		f.write(f' editPan="{level.edit_pan}"')
		f.write(f' editWorkMode="{level.edit_work_mode}"')
		f.write(">")

		# entitny
		f.write("<entities>")
		for entity in level.entities:
			if entity is DudeEntity:
				dude = cast(DudeEntity, entity)
				f.write('<dude')
				f.write(f' name="{dude.name}')
				f.write(f' pos="{dude.position.x} {dude.position.y}"')
				f.write(f' rot="{dude.rotation}"')
				f.write('/>')

			if entity is BodyEntity:
				# body entities are fun since there's a billion optional attributes
				body = cast(BodyEntity, entity)
				f.write('<body')
				if body.template is not None:
					f.write(f' template="{body.template}"')
				f.write(f' pos="{body.position.x} {body.position.y}"')
				f.write(f' rot="{body.rotation}"')
				f.write(f' category="{body.category}"')
				f.write(f' color="{body.color.x} {body.color.y} {body.color.z} {body.color.w}"')
				f.write(f' z="{body.z}"')
				f.write(f' depth="{body.depth}"')
				if body.edge is not None:
					f.write(f' edge="{body.edge.x} {body.edge.y}"')
				if body.group is not None:
					f.write(f' __group="{body.group}"')
				if body.mapping is not None:
					f.write(f' mapping="{body.mapping}"')
				if body.curve is not None:
					f.write(f' curve="{body.curve}"')
				if body.extra_rotation is not None:
					f.write(f' extrarot="{body.extra_rotation.x} {body.extra_rotation.y} {body.extra_rotation.z}"')
				if body.mask is not None:
					f.write(f' mask="{body.mask}"')
				if body.hidden is not None:
					f.write(f' hidden="{int(body.hidden)}"')
				if body.surface is not None:
					f.write(f' surface="{body.surface}"')
				f.write("/>")

				# the actualfuckng
				f.write('<curve>')
				for curve in body.points:
					# FIXME is this even the right order
					f.write(f'<v>{curve.x1} {curve.y1} {curve.c1} {curve.x2} {curve.y2} {curve.c2}</v>')
				f.write('</curve>')
				f.write('</body>')

			if entity is PowerupEntity:
				assert False, "todo"

			if entity is BreakableEntity:
				assert False, "todo"

			if entity is SensorEntity:
				assert False, "todo"

			if entity is JointEntity:
				assert False, "todo"


		f.write("</entities>")
		f.write('</level>\n')
