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
		registerBoolSetting("Netherite", &debris, debris, "Netherite: Enable or disable the collection of netherite");
		registerBoolSetting("Diamonds", &diamonds, diamonds, "Diamonds: Enable or disable the collection of diamonds");
		registerBoolSetting("Emeralds", &emeralds, emeralds, "Emeralds: Enable or disable the collection of emeralds");
		registerBoolSetting("Iron", &iron, iron, "Iron: Enable or disable the collection of iron");
		registerBoolSetting("Gold", &gold, gold, "Gold: Enable or disable the collection of gold");
		registerBoolSetting("Coal", &coal, coal, "Coal: Enable or disable the collection of coal");
		registerBoolSetting("Redstone", &redstone, redstone, "Redstone: Enable or disable the collection of redstone");
		registerBoolSetting("Lapis", &lapis, lapis, "Lapis: Enable or disable the collection of lapis lazuli");
		registerBoolSetting("Other", &other, other, "Other: Enable or disable the collection of other resources");
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