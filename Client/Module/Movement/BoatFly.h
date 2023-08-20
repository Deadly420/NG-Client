#pragma once
#include "../Module.h"
#include "../ModuleManager.h"

class BoatFly : public Module {
private:
	float speed2 = 0.75f;   // speed = 75
	float upspeed = 0.75f;  // speed = 75

public:
	BoatFly();
	~BoatFly();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onMove(MoveInputHandler* input) override;
};