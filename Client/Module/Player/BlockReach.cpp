#include "BlockReach.h"

BlockReach::BlockReach() : Module(0x0, Category::PLAYER, "Exteneded reach for placing/breaking blocks.") {
	registerFloatSetting("Reach", &blockReach, blockReach, 7, 255, "Exteneded Reach With The Slider");
}

BlockReach::~BlockReach() {
}

const char* BlockReach::getModuleName() {
	return ("BlockReach");
}
