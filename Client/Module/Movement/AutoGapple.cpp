#include "AutoGapple.h"

AutoGapple::AutoGapple() : Module(0x0, Category::MOVEMENT, "Auto eat gapples if you're at low health.") {
	registerIntSetting("Health", &health, health, 1, 20, "Health: Set the health value from 1 to 20");
}

AutoGapple::~AutoGapple() {
}

const char* AutoGapple::getModuleName() {
	return ("AutoGapple");
}

void AutoGapple::onTick(GameMode* gm) {
	
}
