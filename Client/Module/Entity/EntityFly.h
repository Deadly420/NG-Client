#pragma once
#include "../Module.h"
#include "../ModuleManager.h"

class EntityFly : public Module {
private:
	bool keyPressed = false;
	float speed2 = 0.75f;   // speed = 75
	float upspeed = 0.75f;  // speed = 75
	float glideMod = 0.f;
	float glideModEffective = 0;

public:
	EntityFly();
	~EntityFly();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onMove(MoveInputHandler* input) override;
};