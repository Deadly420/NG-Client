#pragma once

#include "..\ModuleManager.h"
#include "../Module.h"

class AntiVoid : public Module {
private:
	int distance = 5;
	Vector3 savepos;

public:
	MoveInputHandler* inputHandler = nullptr;
	AntiVoid();
	~AntiVoid();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
