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

constexpr const char* VERSION_STR = "v1";
constexpr uint32 VERSION_NUM = 1;

} // namespace gsm
