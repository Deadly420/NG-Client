#pragma once

#include "../Module.h"

class Freelook : public Module {
public:
	Vector2 oldPos;
	Vector2 Pos;
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