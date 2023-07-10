#pragma once

#include "Module.h"

class Spider : public Module {
private:
	float speed = 0.6f;
	bool dontOvershoot = true;

public:
	Spider();
	~Spider();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onMove(MoveInputHandler* input) override;
};
