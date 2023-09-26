#pragma once
#include "../Module.h"
#include "../../Manager/ModuleManager.h"
class Xray : public Module {
public:
	bool* smoothLightningSetting = nullptr;
	bool gotSmoothInfo = false;
	bool wasSmooth = false;

	Xray() : Module(0x0, Category::RENDER, "Allows you to see certain blocks easier") {};
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