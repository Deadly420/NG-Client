#pragma once

#include "Module.h"

class Jesus :
	public Module
{
private:
	bool wasInWater = false;
public:
	Jesus();
	~Jesus();
	
	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};

