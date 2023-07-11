#include "Teams.h"

Teams::Teams() : Module(0x0, Category::COMBAT, "Don't attack team members!") {
	registerBoolSetting("Is Allied", &alliedCheck, alliedCheck);
	registerBoolSetting("Same Color", &colorCheck, colorCheck);
}

Teams::~Teams() {
}

const char* Teams::getModuleName() {
	return ("Teams");
}
