#pragma once

#include "../Module.h"

class NoWeb : public Module {
public:
	NoWeb();
	~NoWeb();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
