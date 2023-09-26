#pragma once

#include "../Module.h"
#include "../../Manager/ModuleManager.h"

class TriggerBot : public Module {
private:
	int delay = 0;
	int minD = 0;
	int maxD = 20;
	bool sword = true;

public:
	TriggerBot();
	~TriggerBot();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
