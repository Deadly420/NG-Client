#pragma once
#include "../Module.h"
#include "../ModuleManager.h"
class FPS : public Module {
public:
	float scale = 1.f;
	float fpsX = 0.f;
	float fpsY = 280.5f;

	FPS() : Module(0x0, Category::RENDER, "Frames Per Second") {
		registerFloatSetting("Pos-X", &fpsX, fpsX, 0.f, Game.getClientInstance()->getGuiData()->windowSize.x, "Pos-X: Set the horizontal position from 0 to the window width");
		registerFloatSetting("Pos-Y", &fpsY, fpsY, 0.f, Game.getClientInstance()->getGuiData()->windowSize.y, "Pos-Y: Set the vertical position from 0 to the window height");
		registerFloatSetting("Size", &scale, scale, 0.1f, 1.5f, "Size: Adjust the size from 0.1 to 1.5");
	};
	~FPS(){};

	void onPostRender(MinecraftUIRenderContext* renderCtx) {
		// fps
		float f = 10.f * scale;
		std::string tempStr("Movement");
		float len = DrawUtils::getTextWidth(&tempStr, scale) + 7.f;
		float yVal = fpsY;
		float xVal = fpsX;

		if (!(Game.getLocalPlayer() == nullptr)) {
			std::string fpsText = "FPS: " + std::string(WHITE) + std::to_string(Game.getFPS());
			Vec4 rectPos = Vec4(0.5f, yVal + 20.5f * scale, len - 1.5f, yVal + 30.5f * scale);
			Vec2 textPos = Vec2(xVal, yVal);
			DrawUtils::drawText(Vec2{textPos}, &fpsText, Mc_Color(255, 255, 255), scale);
		}
		yVal += f;
	}

	virtual const char* getModuleName() override {
		return "FPS";
	}

	std::string getModSettings() {
		return "Size: " + std::to_string((int)floorf((scale + 0.001f) * 100)) + "%";
	}
};