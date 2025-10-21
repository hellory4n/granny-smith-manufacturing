#pragma once
#include <trippin/memory.h>

#include <GLFW/glfw3.h>
#include <nanovg/nanovg.h>

namespace gsm {

extern struct GrannySmithManufacturing
{
	GLFWwindow* window;
	NVGcontext* vg;
	tr::Arena asset_arena;
} _gsm;

} // namespace gsm
