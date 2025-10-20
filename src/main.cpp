#include <trippin/common.h>
#include <trippin/log.h>

#include <GL/gl.h>
#include <imgui.h>

#include "state.h"
#include "window.h"

int main()
{
	tr::use_log_file("log.txt");
	tr::init();
	TR_DEFER(tr::free());

	gsm::init_window();
	TR_DEFER(gsm::free_window());

	while (!glfwWindowShouldClose(gsm::_gsm.window)) {
		gsm::start_main_loop();

		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui::ShowDemoWindow();

		gsm::end_main_loop();
	}
}
