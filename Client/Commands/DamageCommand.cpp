#include "DamageCommand.h"

#include "../Manager/ModuleManager.h"

DamageCommand::DamageCommand() : Command("damage", "Damage yourself (relies on falldamage)", "<amount>") {
	registerAlias("dmg");
}

DamageCommand::~DamageCommand() {
}

bool DamageCommand::execute(std::vector<std::string>* args) {
	assert(Game.getLocalPlayer() != nullptr);
	float amount = stof(args->at(1));
	if (amount <= 0.0f) {
		clientMessage("%sPlease enter a number greater than 0.", RED);
		return true;
	}
	auto noFallMod = moduleMgr->getModule<NoFall>();
	bool isEnabled = noFallMod->isEnabled();
	if (isEnabled) {
		noFallMod->setEnabled(false);
		Game.getLocalPlayer()->causeFallDamage(amount + 3.f, 1, 0);
		noFallMod->setEnabled(true);
	} else {
		Game.getLocalPlayer()->causeFallDamage(amount + 3.f, 1, 0);
	}
	return true;
}
