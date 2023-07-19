#include "FastUse.h"
FastUse::FastUse() : Module(0x0, Category::COMBAT, "Uses Bow Faster") {
	registerIntSetting("Delay", &charge, charge, 1, 20);
}
FastUse::~FastUse() {
}

const char* FastUse::getModuleName() {
	return "FastBow";
}

void FastUse::onTick(GameMode* gameMode) {
	if (!gameMode) return;

	auto player = Game.getLocalPlayer();
	if (!player) return;

	if (Game.isLeftClickDown) {
		i++;

		if (i >= charge) {
			gameMode->releaseUsingItem();
			i = 0;
		}
	}
}
