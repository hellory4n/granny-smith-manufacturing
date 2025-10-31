import { Context } from "./ctx";
import { Level } from "./level";
import { Vec2 } from "./lib";

export function msgLoadXml(ctx: Context, msg: string): void {
	// the xml is sent as part of the type string
	const xml = msg.substring("open-xml:".length);

	// set everything already so typescript doesn't shit itself
	const level: Level = {
		background: "",
		startDelay: 0,
		startDelayHard: 0,
		grass: "",
		decals: "",
		badGuySpeed: 0,
		badGuySpeedHard: 0,
		gravity: 0,
		backgroundScrollSpeed: 0,
		timeScale: 0,
		clearmem: 0,
		editZoom: 0,
		editPan: new Vec2(0, 0),
		editWorkMode: 0,
		entities: [],
	};

	console.log("loading level xml");
	console.assert(xml.charAt(0) == "<");

	console.log("parsed level xml");
	ctx.current_level = level;
}
