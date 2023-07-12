#pragma once

#include "../../../Utils/Target.h"
#include "../ModuleManager.h"
#include "../Module.h"

class Hitbox : public Module {
public:
	float height = 2;
	float width = 4;
	float range = 8;

	Hitbox();
	~Hitbox();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
};
