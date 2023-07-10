#pragma once

#include "Module.h"

class InventoryMove : public Module {
private:
	bool keyPressed = false;

public:
	InventoryMove();
	~InventoryMove();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
