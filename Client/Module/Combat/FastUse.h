#pragma once
#include "../Module.h"
class FastUse : public Module {
private:
	int charge = 7;
	int i = 0;

public:
	FastUse();
	~FastUse();

	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gameMode) override;
};