#pragma once

#include "Module.h"

class AirSwim : public Module {
public:
	AirSwim();
	~AirSwim();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onEnable() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onDisable() override;
};