#pragma once

#include "../Module.h"

class AntiInvis : public Module {
public:
	AntiInvis();
	~AntiInvis();

	// Inherited from IModule
	virtual const char* getModuleName() override;
};
