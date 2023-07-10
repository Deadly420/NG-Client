#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class TimeChanger : public Module {
public:
	TimeChanger();
	~TimeChanger();

	float modifier = 0.5f;

	// Inherited via Module
	virtual const char* getModuleName() override;
};
