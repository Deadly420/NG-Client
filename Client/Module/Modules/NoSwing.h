#pragma once
#include "Module.h"

class NoSwing : public Module {
public:
	bool server = false;
	NoSwing();
	~NoSwing();

	// Inherited via Module
	virtual const char* getModuleName() override;
};