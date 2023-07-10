#pragma once

#include "Module.h"

class FastLadder : public Module {
public:
	float speed = 0.6f;

	FastLadder();
	~FastLadder();

	// Inherited via Module
	virtual const char* getModuleName() override;
};
