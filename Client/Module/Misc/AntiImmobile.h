#pragma once
#include "../Module.h"
#include "../../Manager/ModuleManager.h"
class AntiImmobile : public Module {
public:
	AntiImmobile() : Module(0x0, Category::MOVEMENT, "Disables immobile flag set by some servers to prevent you from moving"){};
	~AntiImmobile(){};

	virtual const char* getModuleName() override {
		return "AntiImmobile";
	}
};