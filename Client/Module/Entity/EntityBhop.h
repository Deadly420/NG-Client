#pragma once
#include "../Module.h"
#include "../ModuleManager.h"

class EntityBhop : public Module {
private:
	int counter = 1;

public:
	bool lowhop = true;
	float upVal = 0.325f;
	float speed = 0.325f;

	EntityBhop();
	~EntityBhop();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onMove(MoveInputHandler* input) override;
};