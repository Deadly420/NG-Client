#include "AirJump.h"

AirJump::AirJump() : Module(0x0, Category::MOVEMENT, "Jump even you're not on the ground.") {
	registerBoolSetting("Legacy", &legacyMode, legacyMode, "Legacy: Enable or disable legacy mode");
}

AirJump::~AirJump() {
}

const char* AirJump::getModuleName() {
	return ("AirJump");
}

void AirJump::onTick(GameMode* gm) {
	if (legacyMode) {
		gm->player->setOnGround(true);
		return;
	}
	GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();

	if (input == nullptr)
		return;

	if (GameData::isKeyDown(*input->spaceBarKey) && hasJumped == 0) {
		gm->player->setOnGround(true);
		hasJumped = 1;
	} else if (!GameData::isKeyDown(*input->spaceBarKey)) {
		hasJumped = 0;
	}
}
