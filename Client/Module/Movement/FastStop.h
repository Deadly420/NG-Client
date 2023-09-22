#pragma once

#include "../ModuleManager.h"
#include "../Module.h"

class FastStop : public Module {
public:

	FastStop() : Module(0x0, Category::MOVEMENT, "Stop. but fast!") {};
	~FastStop(){};

	virtual const char* getModuleName() override { return "FastStop"; }

	void onMove(MoveInputHandler* input) {
		if (Game.getLocalPlayer() != nullptr && Game.getLocalPlayer()->isAlive()) {
			LocalPlayer* player = Game.getLocalPlayer();

			if (!input->isPressed()) {
				player->location->velocity.x = 0.0f;
				player->location->velocity.z = 0.0f;
			}
		}
	}
};