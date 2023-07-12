#pragma once

#include "../Module.h"

class AutoGapple : public Module {
private:
	int health;

public:
	MoveInputHandler* inputHandler = nullptr;
	AutoGapple();
	~AutoGapple();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
