#pragma once

#include "../Module.h"

class RainbowSky : public Module {
public:
	RainbowSky();
	~RainbowSky();

	// Inherited via Module
	virtual const char* getModuleName() override;
};
