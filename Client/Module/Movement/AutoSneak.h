#pragma once

#include "../Module.h"
class AutoSneak : public Module {
private:
	

public:
	bool doSilent = false;
	AutoSneak();
	~AutoSneak();

	virtual void onDisable() override;
	virtual void onEnable() override;

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
