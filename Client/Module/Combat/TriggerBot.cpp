#include "TriggerBot.h"

#include "../../../Utils/Target.h"

TriggerBot::TriggerBot() : Module(0x0, Category::COMBAT, "Attacks player you're looking at.") {
	registerIntSetting("MinDelay", &minD, 0, 0, 20);
	registerIntSetting("MaxDelay", &maxD, 0, 0, 20);
}

TriggerBot::~TriggerBot() {
}

const char* TriggerBot::getModuleName() {
	return ("TriggerBot");
}
void TriggerBot::onTick(GameMode* gm) {
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	Entity* target = Game.getLocalPlayer()->level->getEntity();
	
	delay++;
	if (target != 0 && delay >= random(minD, maxD)) {
		if (!Target::isValidTarget(target))
			return;

		localPlayer->swingArm();
		gm->attack(target);

	delay = 0;
	}
}