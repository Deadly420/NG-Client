#pragma once

#include "../Module.h"

class AutoSprint : public Module {
private:
	bool alldirections = true;

public:
	AutoSprint();
	~AutoSprint();

	// Inherited via Module
	virtual void onTick(GameMode* gm) override;
	virtual const char* getModuleName() override;
};
