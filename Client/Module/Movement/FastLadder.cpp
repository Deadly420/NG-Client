#include "FastLadder.h"

FastLadder::FastLadder() : Module(0x0, Category::MOVEMENT, "Climb up ladders faster.") {
	registerFloatSetting("Speed", &speed, speed, 0.1f, 1.0f, "Speed: Adjust the speed from 0.1 to 1.0");
}

FastLadder::~FastLadder() {
}

const char* FastLadder::getModuleName() {
	return ("FastLadder");
}
