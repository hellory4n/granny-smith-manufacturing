#include <trippin/common.h>
#include <trippin/log.h>
#include <trippin/math.h>

#include <GL/gl.h>
#include <imgui.h>

#include "gfx.h"
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
		gsm::clear_screen(tr::COLOR_WHITE);
		ImGui::ShowDemoWindow();
		gsm::end_main_loop();
	}
}
