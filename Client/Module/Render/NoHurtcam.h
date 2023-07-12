#pragma once

#include "../Module.h"

class NoHurtcam : public Module{
public:
	NoHurtcam();
	~NoHurtcam();
	
	const char* getModuleName() override;
};
