#pragma once
#include <trippin/memory.h>

#include <GLFW/glfw3.h>

namespace gsm {

extern struct GrannySmithManufacturing
{
	GLFWwindow* window;
	tr::Arena asset_arena;
} _gsm;

} // namespace gsm
