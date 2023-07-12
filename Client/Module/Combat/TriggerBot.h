#pragma once

#include "../Module.h"
#include "../ModuleManager.h"

class TriggerBot : public Module {
private:
	int delay = 0;
	int Odelay = 0;
	bool sword = true;

public:
	TriggerBot();
	~TriggerBot();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
