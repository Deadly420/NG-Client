#pragma once

#include "../Module.h"

class Freelook : public Module {
public:
	Vec2 oldPos;
	Vec2 Pos;
	bool hold = true;

	Freelook() : Module(0x0, Category::RENDER, "Look around freely without moving your rotation.") {
		registerBoolSetting("Hold", &hold, hold, "Hold: Enable or disable the 'Hold' feature.");
	}
	~Freelook(){};

	virtual const char* getModuleName() override {
		return "Freelook"; 
	}

	void onEnable() override { 
		if (Game.getLocalPlayer() != nullptr)
			oldPos = Game.getLocalPlayer()->getActorHeadRotationComponent()->rot;
	}

	void onDisable() override { 
		Game.getLocalPlayer()->getActorHeadRotationComponent()->rot = oldPos; 
	}

	virtual bool isFlashMode() override {
		return hold;
	};
};