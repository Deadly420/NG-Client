#pragma once

#include "../../Manager/ModuleManager.h"
#include "../Module.h"

class Zoom : public Module {
public:
	float strength = 0.5f;

	Zoom() : Module(0x0, Category::RENDER, "Zoom in or out!") {
		registerFloatSetting("Strength", &strength, strength, 0.f, 1.f, "Strength: Adjust the strength from 0.0 to 1.0");
	};
	~Zoom(){};

	virtual const char* getModuleName() override {
		return "Zoom";
	}

	void onLevelRender() override {
		if (auto localPlayer = Game.getLocalPlayer())
			localPlayer->SetFieldOfView(1.f - strength);
	}

	void onDisable() override {
		if (auto localPlayer = Game.getLocalPlayer())
			localPlayer->SetFieldOfView(1.0f);
	}

	bool isFlashMode() override {
		return true;
	}
};