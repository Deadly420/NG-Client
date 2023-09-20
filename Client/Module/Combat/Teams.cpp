#include "Teams.h"

Teams::Teams() : Module(0x0, Category::COMBAT, "Don't attack team members!") {
	registerBoolSetting("Is Allied", &alliedCheck, alliedCheck, "Toggle allied check");
	registerBoolSetting("Same Color", &colorCheck, colorCheck, "Toggle same color check");
}

Teams::~Teams() {
}

const char* Teams::getModuleName() {
	return ("Teams");
}
