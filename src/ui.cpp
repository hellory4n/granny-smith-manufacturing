#include "ui.h"

#include <trippin/common.h>
#include <trippin/iofs.h>
#include <trippin/memory.h>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>

#include "state.h"

// yea
using namespace ImGui;

void gsm::setup()
{
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF(
		tr::path(tr::scratchpad(), "app://FunnelSans-Regular.ttf"), 18
	);

	// theme
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.07f, 0.9f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.447f, 0.223f, 0.886f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(8.00f, 8.00f);
	style.FramePadding = ImVec2(5.00f, 2.00f);
	style.CellPadding = ImVec2(6.00f, 6.00f);
	style.ItemSpacing = ImVec2(6.00f, 6.00f);
	style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
	style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style.IndentSpacing = 25;
	style.ScrollbarSize = 15;
	style.GrabMinSize = 10;
	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	style.FrameBorderSize = 1;
	style.TabBorderSize = 1;
	style.WindowRounding = 2;
	style.ChildRounding = 2;
	style.FrameRounding = 1;
	style.PopupRounding = 2;
	style.ScrollbarRounding = 9;
	style.GrabRounding = 3;
	style.LogSliderDeadzone = 4;
	style.TabRounding = 4;
}

void gsm::dockspace()
{
	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_MenuBar;

	ImGuiViewport* viewport = GetMainViewport();
	SetNextWindowPos(viewport->Pos);
	SetNextWindowSize(viewport->Size);
	SetNextWindowViewport(viewport->ID);

	PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	Begin("Granny Smith Manufacturing", nullptr, window_flags);
	TR_DEFER(End());
	PopStyleVar();

	gsm::menu_bar();

	ImGuiID dockspace_id = GetID("dockspacema");
	DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));

	// default dock stuff
	// TODO wtf is this
	// static bool is_first_time = true;
	// if (is_first_time) {
	// 	DockBuilderRemoveNode(dockspace_id);
	// 	DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
	// 	DockBuilderSetNodeSize(dockspace_id, GetMainViewport()->Size);

	// 	ImGuiID dock_main_id = dockspace_id;
	// 	ImGuiID dock_id_left = DockBuilderSplitNode(
	// 		dock_main_id, ImGuiDir_Left, 0.26f, nullptr, nullptr
	// 	);
	// 	ImGuiID dock_id_left_top;
	// 	ImGuiID dock_id_left_bottom = DockBuilderSplitNode(
	// 		dock_id_left, ImGuiDir_Down, 0.35f, nullptr, &dock_id_left_top
	// 	);
	// 	ImGuiID dock_id_left_bottom_top;
	// 	ImGuiID dock_id_left_bottom_bottom = DockBuilderSplitNode(
	// 		dock_id_left_bottom, ImGuiDir_Down, 0.5f, nullptr, &dock_id_left_bottom_top
	// 	);

	// 	DockBuilderDockWindow("debug", dock_id_left_top);
	// 	DockBuilderDockWindow("about", dock_id_left_bottom_top);
	// 	DockBuilderDockWindow("help", dock_id_left_bottom_bottom);

	// 	DockBuilderFinish(dockspace_id);

	// 	is_first_time = false;
	// }
}

void gsm::menu_bar()
{
	TR_DEFER(EndMenuBar());
	if (BeginMenuBar()) {
		if (BeginMenu("File")) {
			TR_DEFER(EndMenu());
			MenuItem("New", "Ctrl+N");
			MenuItem("Open...", "Ctrl+O");
			MenuItem("Save", "Ctrl+S");
			MenuItem("Save as...", "Ctrl+Shift+S");
			Separator();
			MenuItem("Quit", "Ctrl+Q");
		}
		if (BeginMenu("Edit")) {
			TR_DEFER(EndMenu());
			MenuItem("Undo", "Ctrl+Z");
			MenuItem("Redo", "Ctrl+Shift+Z");
			Separator();
			MenuItem("Cut", "Ctrl+X");
			MenuItem("Copy", "Ctrl+C");
			MenuItem("Paste", "Ctrl+V");
		}
		if (BeginMenu("Help")) {
			TR_DEFER(EndMenu());
			MenuItem("About", nullptr, &_gsm.show_about);
		}
	}
}

void gsm::popups()
{
	if (_gsm.show_about) {
		gsm::about();
	}
}

void gsm::about()
{
	TR_DEFER(End());
	if (!Begin("About", &_gsm.show_about, ImGuiWindowFlags_AlwaysAutoResize)) {
		return;
	}
	Text("Granny Smith Manufacturing %s", VERSION_STR);
	Text("Copyright (c) 2025 hellory4n <hellory4n@gmail.com>");
	Text("Licensed under the zlib/libpng license");
	TextLinkOpenURL("GitHub", "https://github.com/hellory4n/granny-smith-manufacturing");
	Separator();
	Text("Using:");
	BulletText("libtrippin %s", tr::VERSION);
	BulletText("Using GLFW %s", glfwGetVersionString());
	BulletText("Using Dear ImGui %s", IMGUI_VERSION);
}
