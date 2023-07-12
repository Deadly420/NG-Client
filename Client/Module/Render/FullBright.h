#pragma once

#include "../Module.h"

class FullBright : public Module {
public:
	float intensity = 25.f;
	float* gammaPtr = nullptr;
	FullBright();
	~FullBright();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
