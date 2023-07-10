#pragma once

#include "Module.h"

class OffhandAllow : public Module {
public:
	OffhandAllow();
	~OffhandAllow();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
};