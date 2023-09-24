#include "TimeChanger.h"

TimeChanger::TimeChanger() : Module(0x0, Category::RENDER, "Changes the clientside time.") {
	registerFloatSetting("Modifier", &modifier, modifier, 0.1f, 1.f, "Modifier: Adjust the time modifier from 0.1 to 1.0. (Changes the clientside time)");
}

TimeChanger::~TimeChanger() {
}

// Minecraft.Windows.exe+31684A0 
// 44 8B C2 B8 ? ? ? ? F7 EA

const char* TimeChanger::getModuleName() {
	return "TimeChanger";
}
