#pragma once

#include "../Module.h"

class Phase : public Module {
public:
	Phase();
	~Phase();

	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onDisable() override;
};
