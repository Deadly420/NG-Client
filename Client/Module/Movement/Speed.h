#pragma once

#include "../Module.h"

class Speed : public Module {
private:
	float origSpeed = 0;
	float speed = 1.6f;

public:
	Speed();
	~Speed();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
