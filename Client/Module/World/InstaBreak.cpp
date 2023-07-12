#include "InstaBreak.h"

InstaBreak::InstaBreak() : Module(0x0, Category::WORLD, "Break any block instantly.") {
}

InstaBreak::~InstaBreak() {
}

const char* InstaBreak::getModuleName() {
	return ("InstaBreak");
}
