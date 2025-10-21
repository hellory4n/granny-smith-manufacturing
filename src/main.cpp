#include <trippin/common.h>
#include <trippin/log.h>
#include <trippin/math.h>

#include <imgui.h>

#include "gfx.h"
#include "nanovg/nanovg.h"
#include "state.h"
#include "trippin/iofs.h"
#include "ui.h"
#include "window.h"

using gsm::_gsm;

int main()
{
	tr::use_log_file("log.txt");
	tr::set_paths("assets", "granny-smith-manufacturing");
	tr::init();
	TR_DEFER(tr::free());

	gsm::init_window();
	TR_DEFER(gsm::free_window());

	gsm::setup();

	while (!glfwWindowShouldClose(gsm::_gsm.window)) {
		gsm::start_main_loop();
		gsm::clear_screen(tr::COLOR_WHITE);

		gsm::dockspace();
		gsm::scene();
		gsm::inspector();
		gsm::level_settings();
		gsm::tools();

		nvgBeginPath(_gsm.vg);
		nvgMoveTo(_gsm.vg, 52, 67);
		nvgLineTo(_gsm.vg, 71, 197);
		nvgStrokeColor(_gsm.vg, nvgRGBA(0, 0, 0, 180));
		nvgStrokeWidth(_gsm.vg, 3.0f);
		nvgStroke(_gsm.vg);

		gsm::end_main_loop();
	}
}
