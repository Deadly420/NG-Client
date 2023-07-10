#pragma once

#include "../ModuleManager.h"
#include "Module.h"

class NightMode : public Module {
public:
	NightMode();
	~NightMode();

	float modifier = 0.5f;

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
};
