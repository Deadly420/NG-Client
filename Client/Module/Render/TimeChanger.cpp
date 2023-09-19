#include "TimeChanger.h"

TimeChanger::TimeChanger() : Module(0x0, Category::RENDER, "Changes the clientside time.") {
	registerFloatSetting("Modifier", &modifier, modifier, 0.1f, 1.f, "Modifier: Adjust the time modifier from 0.1 to 1.0. (Changes the clientside time)");
}

TimeChanger::~TimeChanger() {
}

const char* TimeChanger::getModuleName() {
	return "TimeChanger";
}
