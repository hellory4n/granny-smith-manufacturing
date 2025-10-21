#include "window.h"

#include <trippin/common.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg/nanovg.h>
#include <nanovg/nanovg_gl.h>

#include "state.h"

void gsm::init_window()
{
	if (!glfwInit()) {
		tr::panic("glfw busted");
	}

	glfwSetErrorCallback([](int error, const char* description) {
		tr::panic("glfw error %i: %s", error, description);
	});

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_DEBUG, true);

	_gsm.window = glfwCreateWindow(800, 600, "Granny Smith Manufacturing", nullptr, nullptr);
	if (_gsm.window == nullptr) {
		tr::panic("window busted");
	}

	glfwMakeContextCurrent(_gsm.window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1);

	glfwSetFramebufferSizeCallback(_gsm.window, [](GLFWwindow* win, int w, int h) {
		(void)win;
		glViewport(0, 0, w, h);
	});
	int w, h;
	glfwGetWindowSize(_gsm.window, &w, &h);
	glViewport(0, 0, w, h);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplGlfw_InitForOpenGL(_gsm.window, true);
	ImGui_ImplOpenGL3_Init();

	_gsm.vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
	if (_gsm.vg == nullptr) {
		tr::panic("nanovg busted");
	}

	tr::log("initialized window and stuff");
}

void gsm::free_window()
{
	nvgDeleteGL3(_gsm.vg);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(_gsm.window);
	glfwTerminate();

	tr::log("deinitialized window and stuff");
}

void gsm::start_main_loop()
{
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	int win_w, win_h;
	glfwGetFramebufferSize(_gsm.window, &win_w, &win_h);
	float32 px_ratio = static_cast<float32>(win_w) / static_cast<float32>(win_h);
	nvgBeginFrame(_gsm.vg, static_cast<float32>(win_w), static_cast<float32>(win_h), px_ratio);
}

void gsm::end_main_loop()
{
	nvgEndFrame(_gsm.vg);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(gsm::_gsm.window);
}
