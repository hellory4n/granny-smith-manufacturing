#include "window.h"

#include <trippin/common.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "state.h"

void gsm::init_window()
{
	if (!glfwInit()) {
		tr::panic("glfw busted");
	}

	glfwSetErrorCallback([](int error, const char* description) {
		tr::panic("glfw error %i: %s", error, description);
	});

	// opengl 2.0 fuck you
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
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

	tr::log("initialized window and stuff");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplGlfw_InitForOpenGL(_gsm.window, true);
	ImGui_ImplOpenGL3_Init();
}

void gsm::free_window()
{
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
}

void gsm::end_main_loop()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(gsm::_gsm.window);
}
