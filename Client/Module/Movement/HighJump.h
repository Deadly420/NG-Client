#pragma once

#include "../Module.h"

class HighJump : public Module {
public:
	float jumpPower = 1.8f;
	HighJump();
	~HighJump();

	// Inherited via Module
	virtual const char* getModuleName() override;
};
