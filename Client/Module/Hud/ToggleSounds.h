#pragma once
#include "../Module.h"
#include "../../Manager/ModuleManager.h"
class ToggleSounds : public Module {
public:
	ToggleSounds() : Module(0x0, Category::HUD, "Play sounds when toggeling modules!"){};
	~ToggleSounds(){};

	virtual const char* getModuleName() override { 
		return "ToggleSounds"; 
	}
};