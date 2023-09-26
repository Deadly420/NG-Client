#pragma once

#include "../../Manager/ModuleManager.h"
#include "../Module.h"

class ChestAura : public Module {
private:
	int range = 3;
	bool enderchests = false;

public:
	MoveInputHandler* inputHandler = nullptr;
	ChestAura();
	~ChestAura();

	std::vector<Vec3i> chestlist;

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onDisable() override;
};
