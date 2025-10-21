#include <trippin/common.h>
#include <trippin/log.h>
#include <trippin/math.h>

#include <imgui.h>

#include "gfx.h"
#include "nanovg/nanovg.h"
#include "state.h"
#include "window.h"

using gsm::_gsm;

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

		nvgBeginPath(_gsm.vg);
		nvgMoveTo(_gsm.vg, 52, 67);
		nvgLineTo(_gsm.vg, 71, 197);
		nvgStrokeColor(_gsm.vg, nvgRGBA(0, 0, 0, 180));
		nvgStrokeWidth(_gsm.vg, 3.0f);
		nvgStroke(_gsm.vg);

		gsm::end_main_loop();
	}
}
