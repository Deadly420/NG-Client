#pragma once

#include "../ModuleManager.h"
#include "../Module.h"

class AirJump : public Module {
private:
	int hasJumped = 0;
	bool legacyMode = false;

public:
	AirJump();
	~AirJump();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
