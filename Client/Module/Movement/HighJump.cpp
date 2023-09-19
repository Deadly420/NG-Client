#include "HighJump.h"

HighJump::HighJump() : Module(0x0, Category::MOVEMENT, "Jump higher than ever before.") {
	registerFloatSetting("Jump Height", &jumpPower, 1, 0.5f, 5.f, "Jump Height: Adjust the jump power from 0.5 to 5.0");
}

HighJump::~HighJump() {
}

const char* HighJump::getModuleName() {
	return ("HighJump");
}
