#pragma once

#include "Module.h"

class Reach : public Module {
private:
	float reachValue = 3;
	float originalReach = 0;
	float* reachPtr = nullptr;
	unsigned long oldProtect = 0;

public:
	Reach();
	~Reach();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual void onTick(GameMode* gm) override;
};
