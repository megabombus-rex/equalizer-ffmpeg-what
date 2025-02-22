#include <iostream>

#include <raylib.h>
#include "DearImGUI/imgui.h"
#include "rlImGUI/rlImGui.h"

int main() {
	int screenWidth = 800;
	int screenHeight = 400;
	int targetFPS = 75;

	bool useDarkTheme = true;
	bool run = true;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Main window");
	SetTargetFPS(targetFPS);
	
	rlImGuiSetup(useDarkTheme);

#ifdef IMGUI_HAS_DOCK
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
#endif

	while (!WindowShouldClose() && run) {
		BeginDrawing();
		rlImGuiBegin();
		
		auto color = Color{ 155, 125, 0, 255 };
		ClearBackground(color);

		if (ImGui::Button("Joe", { 50.0, 50.0 })) {
			std::cout << "DEBUG" << std::endl;
		}

		rlImGuiEnd();
		EndDrawing();
	}

	rlImGuiShutdown();
}