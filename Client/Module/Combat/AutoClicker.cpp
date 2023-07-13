#include "AutoClicker.h"

AutoClicker::AutoClicker() : Module(0, Category::COMBAT, "Automatically clicks for you") {
	registerBoolSetting("Weapons", &weapons, weapons);
	registerBoolSetting("Hold", &hold, hold);
	registerIntSetting("MaxCPS", &maxCPS, maxCPS, 1, 20);
	registerIntSetting("MinCPS", &minCPS, minCPS, 1, 20);
}

const char* AutoClicker::getModuleName() {
	return ("AutoClicker");
}

void AutoClicker::onPlayerTick(Player* plr) {
	if (plr == nullptr) return;

	auto selectedItem = plr->getSelectedItem();
	if (weapons && selectedItem->getAttackingDamageWithEnchants() < 1)
		return;

	if (hold && !Game.isLeftClickDown())
		return;

	if (maxCPS < minCPS) maxCPS = minCPS;
	CPS = random(maxCPS, minCPS);
}

void AutoClicker::onTick(GameMode* gm) {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	auto selectedItem = player->getSelectedItem();
	if (weapons && selectedItem->getAttackingDamageWithEnchants() < 1)
		return;

	if (hold && !Game.isLeftClickDown())
		return;

	static auto clickGuiMod = moduleMgr->getModule<ClickGuiMod>();
	if (Game.canUseMoveKeys() && !clickGuiMod->isEnabled()) {
		Level* pointing = player->level;
		bool isDestroyed = false;

		Game.leftclickCount++;
		player->swing();
		gm->startDestroyBlock(pointing->block, pointing->blockSide, isDestroyed);
		gm->stopDestroyBlock(pointing->block);
		if (isDestroyed && player->region->getBlock(pointing->block)->blockLegacy->blockId != 0) gm->destroyBlock(&pointing->block, 0);
	}
}