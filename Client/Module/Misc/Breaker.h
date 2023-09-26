#pragma once

#include "../Module.h"
#include "../../Manager/ModuleManager.h"

class Breaker : public Module {
private:
	int range = 5;
	bool beds = true;
	bool eggs = true;
	bool cakes = true;
	bool treasures = true;
	bool chests = false;
	bool barrels = false;

public:
	Breaker();
	~Breaker();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
