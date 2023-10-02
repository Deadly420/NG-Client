#pragma once
#include "../../Manager/ModuleManager.h"
#include "../Module.h"
class BPS : public Module {
public:
	bool ImGui = false;
	float scale = 1.f;
	float bpsX = 0.f;
	float bpsY = 270.5f;

	BPS() : Module(0x0, Category::RENDER, "Blocks Per Second") {
		registerBoolSetting("ImGui", &ImGui, ImGui, "Renders With ImGui");
		registerFloatSetting("Pos-X", &bpsX, bpsX, 0.f, Game.getClientInstance()->getGuiData()->windowSize.x, "Pos-X: Adjust the horizontal position from 0 to the window width");
		registerFloatSetting("Pos-Y", &bpsY, bpsY, 0.f, Game.getClientInstance()->getGuiData()->windowSize.y, "Pos-Y: Modify the vertical position from 0 to the window height");
		registerFloatSetting("Size", &scale, scale, 0.1f, 1.5f, "Size: Control the size from 0.1 to 1.5");
	};
	~BPS(){};

	void onImGuiRender() {
		// Main Window
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
		if (ImGui) {
			if (ImGui::Begin("BPS", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {
				auto player = Game.getLocalPlayer();
				ImGui::SetWindowPos(ImVec2(bpsX, bpsY));
				std::string bpsText = "BPS: " + std::to_string((int)player->getBlocksPerSecond()) + std::string(".") + std::to_string((int)(player->getBlocksPerSecond() * 10) - ((int)player->getBlocksPerSecond() * 10));
				// Calculate the size of the text
				ImVec2 textSize = ImGui::CalcTextSize(bpsText.c_str());
				// Set the window size to fit the text
				ImGui::SetWindowSize(textSize);
				ImGui::Text("%s", bpsText.c_str());
				ImGui::End();
			}
		}
	}

	void onPostRender(MinecraftUIRenderContext* renderCtx) {
		// bps
		float f = 10.f * this->scale;
		std::string tempStr("Movement");
		float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;

		float yVal = bpsY;
		float xVal = bpsX;

		if (!(Game.getLocalPlayer() == nullptr)) {
			auto player = Game.getLocalPlayer();
			std::string bpsText = "BPS: " + std::to_string((int)player->getBlocksPerSecond()) + std::string(".") + std::to_string((int)(player->getBlocksPerSecond() * 10) - ((int)player->getBlocksPerSecond() * 10));
			Vec4 rectPos = Vec4(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
			Vec2 textPos = Vec2(xVal, yVal);
			DrawUtils::drawText(Vec2{textPos}, &bpsText, Mc_Color(255, 255, 255), scale);
		}
		yVal += f;
	}

	virtual const char* getModuleName() override {
		return "BPS";
	}

	std::string getModSettings() {
		return "Size: " + std::to_string((int)floorf((scale + 0.001f) * 100)) + "%";
	}
};