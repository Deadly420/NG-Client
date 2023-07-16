#pragma once
#include "../Module.h"
class RainbowSky : public Module {
public:
	float intensity = 0.01f;

	RainbowSky();
	~RainbowSky();

	// Inherited via Module
	virtual const char* getModuleName() override;
	static float red;
	static float green;
	static float blue;
	static bool custom;
};