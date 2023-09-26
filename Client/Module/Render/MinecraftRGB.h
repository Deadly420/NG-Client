#pragma once
#pragma once
#include "../Module.h"
#include "../../Manager/ModuleManager.h"

class MinecraftRGB : public Module {
public:
	float Opacity = 1.f, Red = 1.f, Green = 1.f, Blue = 1.f;
	MinecraftRGB() : Module(0x0, Category::RENDER, "Modifies Minecrafts colors and opacity") {
		registerFloatSetting("Text Opacity", &Opacity, Opacity, 0.f, 1.f, "Text Opacity: Adjust text opacity from 0.0 to 1.0");
		registerFloatSetting("Red", &Red, Red, 0.f, 1.f, "Red: Modify the red component from 0.0 to 1.0");
		registerFloatSetting("Green", &Green, Green, 0.f, 1.f, "Green: Modify the green component from 0.0 to 1.0");
		registerFloatSetting("Blue", &Blue, Blue, 0.f, 1.f, "Blue: Modify the blue component from 0.0 to 1.0");
	};
	~MinecraftRGB(){};

	float* opacityAddress = (float*)(Utils::getBase() + 0x4E37BAC);
	float* redAddress = (float*)(Utils::getBase() + 0x4E37BA0);
	float* greenAddress = (float*)(Utils::getBase() + 0x4E37BA4);
	float* blueAddress = (float*)(Utils::getBase() + 0x4E37BA8);
	void onWorldTick(GameMode* gm) {
		*opacityAddress = 0;
		*opacityAddress = Opacity;
		*redAddress = Red;
		*greenAddress = Green;
		*blueAddress = Blue;
	}

	void onDisable() {
		*opacityAddress = 1.f;
		*redAddress = 1.f;
		*greenAddress = 1.f;
		*blueAddress = 1.f;
	}

	virtual const char* getModuleName() override {
		return "MinecraftRGB";
	}
};