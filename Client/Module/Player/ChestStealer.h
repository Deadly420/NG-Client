#pragma once

#include "../Module.h"

class ChestStealer : public Module {
private:
	int delay = 0;
	int setDelay = 7;
	bool enhanced = true;

public:
	ChestStealer();
	~ChestStealer();

	// Inherited via Module
	virtual void chestScreenController_tick(ChestScreenController* c);
	virtual const char* getModuleName() override;
};
