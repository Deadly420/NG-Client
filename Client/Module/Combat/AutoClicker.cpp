#include "AutoClicker.h"

AutoClicker::AutoClicker() : Module(0, Category::COMBAT, "A simple autoclicker, automatically clicks for you.") {
	// Registering Boolean Settings with Tooltips
	registerBoolSetting("RightClick", &rightclick, rightclick, "Toggle right-click feature");
	registerBoolSetting("Only Weapons", &weapons, weapons, "Toggle only weapons");
	registerBoolSetting("Break Blocks", &breakBlocks, breakBlocks, "Toggle block-breaking");
	registerBoolSetting("Hold", &hold, hold, "Toggle hold mode");

	// Registering Integer Settings
	registerIntSetting("MinDelay", &minD, minD, 0, 20, "Minimum delay setting");
	registerIntSetting("MaxDelay", &maxD, maxD, 0, 20, "Maximum delay setting");
}

AutoClicker::~AutoClicker() {}

const char* AutoClicker::getModuleName() {
	return "AutoClicker";
}

void AutoClicker::onTick(GameMode* gm) {
	if ((GameData::isLeftClickDown() || !hold) && GameData::canUseMoveKeys()) {
		LocalPlayer* player = Game.getLocalPlayer();
		Level* level = player->level;
		delay++;

		if (delay >= random(minD, maxD)) {
			auto selectedItem = player->getSelectedItem();
			if (weapons && selectedItem->getAttackingDamageWithEnchants() < 1)
				return;

			player->swingArm();

			if (level->hasEntity() != 0)
				gm->attack(level->getEntity());
			else if (breakBlocks) {
				bool isDestroyed = false;
				gm->startDestroyBlock(level->block, level->blockSide, isDestroyed);
				gm->stopDestroyBlock(level->block);
				if (isDestroyed && player->getRegion()->getBlock(level->block)->blockLegacy->blockId != 0)
					gm->destroyBlock(&level->block, 0);
			}
			delay = 0;
		}
	}

	if (rightclick) {
		if ((GameData::isRightClickDown() || !hold) && GameData::canUseMoveKeys()) {
			Level* level = Game.getLocalPlayer()->level;
			delay++;
			if (delay >= random(minD, maxD)) {
				bool idk = true;
				gm->buildBlock(new Vec3i(level->block), level->blockSide, idk);
				delay = 0;
			}
		}
	}
}