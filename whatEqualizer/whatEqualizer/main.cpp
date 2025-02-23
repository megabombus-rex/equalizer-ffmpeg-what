#include <iostream>

#include <raylib.h>
#include "DearImGUI/imgui.h"
#include "rlImGUI/rlImGui.h"

float ScaleToDPIF(float value)
{
	return GetWindowScaleDPI().x * value;
}

int ScaleToDPII(int value)
{
	return int(GetWindowScaleDPI().x * value);
}

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 1280;
	int screenHeight = 800;
	int targetFPS = 75;
	bool darkTheme = true;

	// do not set the FLAG_WINDOW_HIGHDPI flag, that scales a low res framebuffer up to the native resolution.
	// use the native resolution and scale your geometry.
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "raylib-Extras [ImGui] example - Docking");
	SetTargetFPS(targetFPS);
	rlImGuiSetup(darkTheme);

	bool run = true;

	bool showDemoWindow = true;

	// if the linked ImGui has docking, enable it.
	// this will only be true if you use the docking branch of ImGui.
#ifdef IMGUI_HAS_DOCK
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
#endif

	// Main game loop
	while (!WindowShouldClose() && run)    // Detect window close button or ESC key, or a quit from the menu
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		// draw something to the raylib window below the GUI.
		DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, GetScreenHeight() * 0.45f, DARKGREEN);

		// start ImGui content
		rlImGuiBegin();

		// if you want windows to dock to the viewport, call this.
#ifdef IMGUI_HAS_DOCK
		ImGui::DockSpaceOverViewport(0, NULL, ImGuiDockNodeFlags_PassthruCentralNode); // set ImGuiDockNodeFlags_PassthruCentralNode so that we can see the raylib contents behind the dockspace
#endif

		// show a simple menu bar
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Quit"))
					run = false;

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("Demo Window", nullptr, showDemoWindow)) {
					showDemoWindow = !showDemoWindow;
					std::cout << "show demo window is " << showDemoWindow << std::endl;
				}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}


		if (ImGui::Begin("Test Window"))
		{
			ImGui::TextUnformatted("Another window");
		}
		ImGui::End();

		// end ImGui Content
		rlImGuiEnd();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}
	rlImGuiShutdown();

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}