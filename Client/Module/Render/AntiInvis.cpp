#include "AntiInvis.h"

AntiInvis::AntiInvis() : Module(0, Category::RENDER, "See entities with invisibility potion") {}

AntiInvis::~AntiInvis() {}

const char* AntiInvis::getModuleName() {
	return "AntiInvis";
}
