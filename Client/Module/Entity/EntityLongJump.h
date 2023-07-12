#pragma once
#include "../../../Client/Module/Module.h"
#include "..\ModuleManager.h"

class EntityLongJump : public Module {
private:
	int counter = 1;

public:
	float upVal = 0.325f;
	float speed = 0.325f;

	EntityLongJump();
	~EntityLongJump();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onMove(MoveInputHandler* input) override;
};