#pragma once
#include "../Module.h"
#include "../../Manager/ModuleManager.h"
#include "../../../include/imgui/imgui.h"

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
		if (ImGui && Game.getLocalPlayer() != nullptr) {
			static ImVec2 windowPos = ImVec2(0, 260);
			ImGui::SetNextWindowPos(windowPos, ImGuiCond_FirstUseEver);

			if (ImGui::Begin("BPS", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground)) {
				auto player = Game.getLocalPlayer();
				std::string bpsText = "BPS: " + std::to_string((int)player->getBlocksPerSecond()) + std::string(".") + std::to_string((int)(player->getBlocksPerSecond() * 10) - ((int)player->getBlocksPerSecond() * 10));
				ImGui::SetWindowFontScale(1.5);
				ImGui::Text("%s", bpsText.c_str());
				ImGui::End();
			}
		}
	}

	void onPostRender(MinecraftUIRenderContext* renderCtx) {
		if (!ImGui && Game.getLocalPlayer() != nullptr) {
			// bps
			float f = 10.f * this->scale;
			std::string tempStr("Movement");
			float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;

			float yVal = bpsY;
			float xVal = bpsX;

			auto player = Game.getLocalPlayer();
			std::string bpsText = "BPS: " + std::to_string((int)player->getBlocksPerSecond()) + std::string(".") + std::to_string((int)(player->getBlocksPerSecond() * 10) - ((int)player->getBlocksPerSecond() * 10));
			Vec4 rectPos = Vec4(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
			Vec2 textPos = Vec2(xVal, yVal);
			DrawUtils::drawText(Vec2{textPos}, &bpsText, Mc_Color(255, 255, 255), scale);
			yVal += f;
		}
	}

	virtual const char* getModuleName() override {
		return "BPS";
	}

	std::string getModSettings() {
		return "Size: " + std::to_string((int)floorf((scale + 0.001f) * 100)) + "%";
	}
};