#pragma once
#include "../../../Client/Module/Module.h"
#include "../../Manager/ModuleManager.h"
class Velocity : public Module {
public:
	float xModifier = 0.f;
	float yModifier = 0.f;

	Velocity() : Module(0x0, Category::MOVEMENT, "Don't ever take knockback again.") {
		registerFloatSetting("Linear Modifier", &xModifier, xModifier, 0.f, 1.f, "Linear Modifier: Adjust the linear knockback modifier from 0.0 to 1.0. (Controls horizontal knockback)");
		registerFloatSetting("Height Modifier", &yModifier, yModifier, 0.f, 1.f, "Height Modifier: Adjust the height knockback modifier from 0.0 to 1.0. (Controls vertical knockback)");
	};
	~Velocity(){};

	const char* Velocity::getModuleName() {
		return "Velocity";
	}

	std::string Velocity::getModSettings() {
		return std::to_string((int)floorf((xModifier + 0.001f) * 100)) + "% | " + std::to_string((int)floorf((yModifier + 0.001f) * 100)) + "%";
	}
};