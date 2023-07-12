#pragma once

#include "../Module.h"

class InstaBreak : public Module {
public:
	InstaBreak();
	~InstaBreak();
	
	// Inherited via Module
	virtual const char* getModuleName() override;
};
