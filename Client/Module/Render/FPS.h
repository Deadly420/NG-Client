#pragma once

#include "../Module.h"
#include "../../Manager/ModuleManager.h"
#include "../../../include/imgui/imgui.h"

class FPS : public Module {
public:
	bool ImGui = false;
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
		if (ImGui && Game.getLocalPlayer() != nullptr) {
			int screenWidth = GetSystemMetrics(SM_CXSCREEN);
			int screenHeight = GetSystemMetrics(SM_CYSCREEN);

			static ImVec2 windowPos = ImVec2(0, 280);
			ImGui::SetNextWindowPos(windowPos, ImGuiCond_FirstUseEver);

			if (ImGui::Begin("FPS", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground)) {
				std::string fpsText = "FPS: " + std::to_string(Game.getFPS());
				ImGui::SetWindowFontScale(1.5);
				ImGui::Text("%s", fpsText.c_str());
				ImGui::End();
			}
		}
	}

	void onPostRender(MinecraftUIRenderContext* renderCtx) override {
		if (Game.getLocalPlayer() == nullptr) return;

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
