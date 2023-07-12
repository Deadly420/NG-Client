#pragma once
#pragma once
#include "../Module.h"
#include "../ModuleManager.h"

class MinecraftRGB : public Module {
public:
	float Opacity = 1.f, Red = 1.f, Green = 1.f, Blue = 1.f;
	MinecraftRGB() : Module(0x0, Category::RENDER, "Modifies Minecrafts colors and opacity") {
		registerFloatSetting("Text Opacity", &Opacity, Opacity, 0.f, 1.f);
		registerFloatSetting("Red", &Red, Red, 0.f, 1.f);
		registerFloatSetting("Green", &Green, Green, 0.f, 1.f);
		registerFloatSetting("Blue", &Blue, Blue, 0.f, 1.f);
	};
	~MinecraftRGB(){};

	float* opacityAddress = (float*)(Utils::getBase() + 0x4b7745c);
	float* redAddress = (float*)(Utils::getBase() + 0x4b77450);
	float* greenAddress = (float*)(Utils::getBase() + 0x4b77454);
	float* blueAddress = (float*)(Utils::getBase() + 0x4b77458);
	void onTick(GameMode* gm) {
		*opacityAddress = Opacity;
		*redAddress = Red;
		*greenAddress = Green;
		*blueAddress = Blue;
	}
	virtual const char* getModuleName() override {
		return "MinecraftRGB";
	}
};