#pragma once

#include "Module.h"

class Velocity : public Module {
public:
	float xModifier = 0.f;
	float yModifier = 0.f;
	Velocity();
	~Velocity();

	// Inherited via Module
	virtual const char* getModuleName() override;
};
