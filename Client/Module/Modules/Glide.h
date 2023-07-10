#pragma once

#include "Module.h"

class Glide : public Module {
private:
	float glideMod = -0.01f;
	float glideModEffective = 0;

public:
	Glide();
	~Glide();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual const char* getRawModuleName() override;
};