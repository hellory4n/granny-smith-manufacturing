#include "window.h"

#include <trippin/common.h>

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl2.h>

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
	ImGui_ImplOpenGL2_Init();
}

void gsm::free_window()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(_gsm.window);
	glfwTerminate();
}

void gsm::start_main_loop()
{
	glfwPollEvents();
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void gsm::end_main_loop()
{
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(gsm::_gsm.window);
}
