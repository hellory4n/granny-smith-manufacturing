import { Context } from "./ctx";
import { msgLoadXml } from "./uimsg";

figma.showUI(__html__);

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
