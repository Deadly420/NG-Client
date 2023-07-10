#pragma once

#include "Module.h"

class Timer : public Module {
private:
	int timer = 50;

public:
	Timer();
	~Timer();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onTick(GameMode* gm) override;
};
