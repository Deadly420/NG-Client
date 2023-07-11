#include "TimeChanger.h"

TimeChanger::TimeChanger() : Module(0, Category::RENDER, "Changes the clientside time.") {
	registerFloatSetting("Modifier", &modifier, modifier, 0.1f, 1.f);
}

TimeChanger::~TimeChanger() {
}

const char* TimeChanger::getModuleName() {
	return "TimeChanger";
}
