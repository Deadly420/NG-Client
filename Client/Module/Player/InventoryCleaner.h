#pragma once

#include "../Module.h"

class InventoryCleaner : public Module {
private:
	bool sorted = false;

	std::vector<int> findStackableItems();
	std::vector<int> findUselessItems();
	bool isLastItem(Item* item);

	bool keepTools = true;
	bool keepArmor = true;
	bool keepBlocks = true;
	bool keepFood = true;

	bool openInv = true;
	bool autoSort = false;

public:
	bool stackIsUseful(ItemStack* itemStack);
	InventoryCleaner();
	~InventoryCleaner();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
