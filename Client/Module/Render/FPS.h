#pragma once

#include "../Module.h"
#include "../ModuleManager.h"
#include "../../../include/imgui/imgui.h"

class FPS : public Module {
public:
	bool ImGui = true;
	float scale = 1.0f;
	float fpsX = 0.0f;
	float fpsY = 280.5f;

	FPS() : Module(0x0, Category::RENDER, "Frames Per Second") {
		registerBoolSetting("ImGui", &ImGui, ImGui, "Renders With ImGui");
		registerFloatSetting("Pos-X", &fpsX, fpsX, 0.0f, Game.getClientInstance()->getGuiData()->windowSize.x, "Pos-X: Set the horizontal position from 0 to the window width");
		registerFloatSetting("Pos-Y", &fpsY, fpsY, 0.0f, Game.getClientInstance()->getGuiData()->windowSize.y, "Pos-Y: Set the vertical position from 0 to the window height");
		registerFloatSetting("Size", &scale, scale, 0.1f, 1.5f, "Size: Adjust the size from 0.1 to 1.5");
	}

	~FPS() {}

	void onImGuiRender() {
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowTitleAlign = ImVec2(0.5, 0.5);
		style->ItemInnerSpacing = ImVec2(8, 6);
		style->WindowPadding = ImVec2(15, 15);
		style->ItemSpacing = ImVec2(12, 8);
		style->FramePadding = ImVec2(5, 5);
		style->ScrollbarRounding = 9.0f;
		style->ScrollbarSize = 15.0f;
		style->IndentSpacing = 25.0f;
		style->WindowRounding = 10.f;
		style->GrabRounding = 3.0f;
		style->FrameRounding = 6.f;
		style->GrabMinSize = 5.0f;

		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_Separator] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
		style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);

		if (ImGui) {
			ImGui::Begin("FPS Counter", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);

			if (Game.getLocalPlayer() != nullptr) {
				// Get the FPS
				float fps = Game.getFPS();

				// Display just the numerical FPS value
				ImGui::Text("FPS: %.1f", fps);
			}

			ImGui::End();
		}
	}

	void onPostRender(MinecraftUIRenderContext* renderCtx) override {
		if (Game.getLocalPlayer() == nullptr) {
			return;
		}
		if (!ImGui) {
			float f = 10.0f * scale;
			std::string fpsText = "FPS: " + std::to_string(Game.getFPS());
			float len = DrawUtils::getTextWidth(&fpsText, scale) + 7.0f;
			float yVal = fpsY;
			float xVal = fpsX;

			Vec4 rectPos = Vec4(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
			Vec2 textPos = Vec2(xVal, yVal);
			DrawUtils::drawText(textPos, &fpsText, Mc_Color(255, 255, 255), scale);

			yVal += f;
		}
	}

	const char* getModuleName() override {
		return "FPS";
	}

	std::string getModSettings() {
		return "Size: " + std::to_string(static_cast<int>(floorf((scale + 0.001f) * 100))) + "%";
	}
};
