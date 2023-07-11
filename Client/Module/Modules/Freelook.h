#pragma once

#include "Module.h"

class Freelook : public Module {
public:
	Vec2 oldPos;
	Vec2 Pos;
	bool hold = true;

	Freelook() : Module(0x0, Category::RENDER, "Look around freely without moving your rotation.") {
		registerBoolSetting("Hold", &hold, hold);
	}
	~Freelook(){};

	virtual const char* getModuleName() override { return "Freelook"; }
	void onEnable() override { 
		if (Game.getLocalPlayer() != nullptr)
		oldPos = Game.getLocalPlayer()->viewAngles; 
	}
	void onDisable() override { Game.getLocalPlayer()->setRot(oldPos); }
	virtual bool isFlashMode() override {
		return hold;
	};
};