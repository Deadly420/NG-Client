#pragma once

#include "../Module.h"

class AutoTotem : public Module {
public:
	AutoTotem();
	~AutoTotem();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
