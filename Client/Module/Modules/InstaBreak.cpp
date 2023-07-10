#include "InstaBreak.h"

InstaBreak::InstaBreak() : Module(VK_NUMPAD4, Category::WORLD, "Break any block instantly.") {
}

InstaBreak::~InstaBreak() {
}

const char* InstaBreak::getModuleName() {
	return ("InstaBreak");
}
