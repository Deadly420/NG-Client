#pragma once
#include "../../Manager/ModuleManager.h"
#include "../Module.h"
class CPS : public Module {
public:
	float scale = 1.f;
	float cpsX = 0.f;
	float cpsY = 290.5f;

	CPS() : Module(0x0, Category::RENDER, "Clicks Per Second") {
		registerFloatSetting("Pos-X", &cpsX, cpsX, 0.f, Game.getClientInstance()->getGuiData()->windowSize.x, "Pos-X: Set the horizontal position from 0 to the window width");
		registerFloatSetting("Pos-Y", &cpsY, cpsY, 0.f, Game.getClientInstance()->getGuiData()->windowSize.y, "Pos-Y: Set the vertical position from 0 to the window height");
		registerFloatSetting("Size", &scale, scale, 0.1f, 1.5f, "Size: Adjust the size from 0.1 to 1.5");
	};
	~CPS(){};

	void onImGuiRender() {}

	void onPostRender(MinecraftUIRenderContext* renderCtx) {
		// CPS
		float f = 10.f * this->scale;
		std::string tempStr("Movement");
		float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;

		float yVal = cpsY;
		float xVal = cpsX;

		if (!(Game.getLocalPlayer() == nullptr)) {
			std::string cpsText = "CPS: " + std::to_string(Game.getLeftCPS()) + " - " + std::to_string(Game.getRightCPS());
			Vec4 rectPos = Vec4(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
			Vec2 textPos = Vec2(xVal, yVal);
			DrawUtils::drawText(Vec2{textPos}, &cpsText, Mc_Color(255, 255, 255), scale);
		}
		yVal += f;
	}

	virtual const char* getModuleName() override {
		return "CPS";
	}

	std::string getModSettings() {
		return "Size: " + std::to_string((int)floorf((scale + 0.001f) * 100)) + "%";
	}
};