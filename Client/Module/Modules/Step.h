#pragma once

#include "Module.h"

class Step : public Module {
private:
	float height = 2.f;

public:
	Step();
	~Step();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onDisable() override;
};
