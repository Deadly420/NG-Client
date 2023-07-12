#pragma once
#include "../../../Client/Module/Module.h"
#include "../ModuleManager.h"

class EntitySpeed : public Module {
private:
	bool keyPressed = false;
	float speed2 = 0.75f;  // speed = 75

public:
	EntitySpeed();
	~EntitySpeed();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};