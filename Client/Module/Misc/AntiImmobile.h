#pragma once

#include "../Module.h"

class AntiImmobile : public Module {
public:
	AntiImmobile();
	~AntiImmobile();

	// Inherited via Module
	const char* getModuleName() override;
};
