#pragma once

#include "../../Manager/ModuleManager.h"
#include "../Module.h"

class Bhop : public Module {
private:
	float speed = 0.325f;
	bool hive = false;
	float speedFriction = 0.65f;
	float cashedStepHeignt = 0.5f;

public:
	Bhop();
	~Bhop();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onMove(MoveInputHandler* input) override;
	virtual void onEnable() {
		auto player = Game.getLocalPlayer();
		if (player == nullptr)
			return;
		else
			cashedStepHeignt = player->getMaxAutoStepComponent()->stepHeight;
	};
	virtual void onDisable() {
		auto player = Game.getLocalPlayer();
		if (player == nullptr)
			return;
		else
			player->getMaxAutoStepComponent()->stepHeight = cashedStepHeignt;
	};
};