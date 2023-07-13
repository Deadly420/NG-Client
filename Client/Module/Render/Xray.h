#pragma once
#include "../Module.h"
#include "../ModuleManager.h"
class Xray : public Module {
public:
	bool* smoothLightningSetting = nullptr;
	bool gotSmoothInfo = false;
	bool wasSmooth = false;
	bool debris = false;
	bool diamonds = false;
	bool emeralds = false;
	bool iron = false;
	bool gold = false;
	bool coal = false;
	bool redstone = false;
	bool lapis = false;
	bool other = false;

	Xray() : Module(0x0, Category::RENDER, "Allows you to see certain blocks easier") {
		registerBoolSetting("Netherite", &debris, debris);
		registerBoolSetting("Diamonds", &diamonds, diamonds);
		registerBoolSetting("Emeralds", &emeralds, emeralds);
		registerBoolSetting("Iron", &iron, iron);
		registerBoolSetting("Gold", &gold, gold);
		registerBoolSetting("Coal", &coal, coal);
		registerBoolSetting("Redstone", &redstone, redstone);
		registerBoolSetting("Lapis", &lapis, lapis);
		registerBoolSetting("Other", &other, other);
	};
	~Xray(){};

	void onTick(GameMode* gm) {
		if (smoothLightningSetting != nullptr) {
			if (!gotSmoothInfo) {
				gotSmoothInfo = true;
				wasSmooth = *smoothLightningSetting;
			}
			*smoothLightningSetting = 0;
		}
	}

	void onDisable() {
		if (smoothLightningSetting != nullptr && gotSmoothInfo) {
			*smoothLightningSetting = wasSmooth;
		}
		gotSmoothInfo = false;
	}

	virtual const char* getModuleName() override {
		return "Xray";
	}
};