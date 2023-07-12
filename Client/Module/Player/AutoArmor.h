#pragma once

#include "../Module.h"

class AutoArmor : public Module {
public:
	CraftingScreenController* inventoryScreen = nullptr;
	AutoArmor();
	~AutoArmor();

	// Inherited via Module
	virtual void onTick(GameMode* gm) override;
	virtual const char* getModuleName() override;
};
