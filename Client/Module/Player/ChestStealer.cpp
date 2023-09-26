#include "ChestStealer.h"
#include "../../Manager/ModuleManager.h"

ChestStealer::ChestStealer() : Module(0x0, Category::PLAYER, "Automatically takes all items out of a chest.") {
	registerIntSetting("Closing Delay", &setDelay, setDelay, 0, 20, "Closing Delay: Adjust the delay from 0 to 20 before closing");
	registerBoolSetting("Enhanced", &enhanced, enhanced, "Enhanced: Enable enhanced mode for improved performance");
}

ChestStealer::~ChestStealer() {
}

const char* ChestStealer::getModuleName() {
	return ("ChestStealer");
}

void ChestStealer::chestScreenController_tick(ChestScreenController* c) {
	if (c == nullptr || Game.getLocalPlayer() == nullptr || Game.getLocalPlayer()->canOpenContainerScreen()) {
		return;  // Exit early if conditions are not met.
	}

	delay++;
	std::vector<int> itemsToSteal;
	auto invcleanerMod = moduleMgr->getModule<InventoryCleaner>();

	for (int i = 0; i < 54; i++) {
		ItemStack* stack = c->_getItemStack(TextHolder("container_items"), i);

		if (stack != nullptr && stack->item != nullptr &&
			(!enhanced || invcleanerMod->stackIsUseful(stack))) {
			itemsToSteal.push_back(i);
		}
	}

	if (!itemsToSteal.empty() && !Game.getLocalPlayer()->getSupplies()->inventory->isFull()) {
		for (int i : itemsToSteal) {
			if (delay > setDelay && setDelay > 0) {
				c->handleAutoPlace("container_items", i);
				delay = 0;
			} else if (setDelay == 0) {
				c->handleAutoPlace("container_items", i);
			}
		}
	} else {
		c->tryExit();
	}
}