#pragma once
#include "../Module.h"
#include "../ModuleManager.h"
class XP : public Module {
public:
	int amount = 1;

	XP() : Module(0x0, Category::PLAYER, "Gives You Shit Loads Of XP!") {
		registerIntSetting("amount", &amount, amount, 1, 5000);
	};
	~XP(){};
	void onTick(GameMode* gm) {
		LocalPlayer* player = Game.getLocalPlayer();
		player->addExperience(amount);
	}

	virtual const char* getModuleName() override {
		return "XP";
	}
};