#pragma once

#include "../../Manager/ModuleManager.h"
#include "../Module.h"

class AutoClicker : public Module {
private:
	int delay = 0;
	int minD = 0;
	int maxD = 20;
	bool weapons = true;
	bool breakBlocks = true;
	bool rightclick = false;
	bool hold = false;

public:
	AutoClicker();
	~AutoClicker();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};