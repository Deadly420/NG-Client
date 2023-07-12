#pragma once

#include "../Module.h"

class MidClick : public Module {
private:
	bool hasClicked = false;

public:
	MidClick();
	~MidClick();
	
	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
