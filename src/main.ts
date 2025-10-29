import { Context } from "./ctx";
import { msgLoadXml } from "./messages";

figma.showUI(__html__);

// typescript really doesn't like global variables
// also this should be `let` but then eslint gets mad even tho i do change it later through another
// function but it still works because this is a language based on hopes and dreams
const ctx: Context = {};

// Calls to "parent.postMessage" from within the HTML page will trigger this
// callback. The callback will be passed the "pluginMessage" property of the
// posted message.
figma.ui.onmessage = (msg: { type: string; count: number }) => {
	if (msg.type.startsWith("open-xml:")) {
		msgLoadXml(ctx, msg.type);
	}

	// if (msg.type === "create-shapes") {
	// 	// This plugin creates rectangles on the screen.
	// 	const numberOfRectangles = msg.count;

	// 	const nodes: SceneNode[] = [];
	// 	for (let i = 0; i < numberOfRectangles; i++) {
	// 		const rect = figma.createEllipse();
	// 		rect.x = i * 150;
	// 		rect.fills = [{ type: "SOLID", color: { r: 1, g: 1, b: 1 } }];
	// 		figma.currentPage.appendChild(rect);
	// 		nodes.push(rect);
	// 	}
	// 	figma.currentPage.selection = nodes;
	// 	figma.viewport.scrollAndZoomIntoView(nodes);
	// }

	// Make sure to close the plugin when you're done. Otherwise the plugin will
	// keep running, which shows the cancel button at the bottom of the screen.
	figma.closePlugin();
};
