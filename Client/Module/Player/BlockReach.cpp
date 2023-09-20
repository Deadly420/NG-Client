#include "BlockReach.h"

BlockReach::BlockReach() : Module(0x0, Category::PLAYER, "Exteneded reach for placing/breaking blocks.") {
	registerFloatSetting("Reach", &blockReach, blockReach, 7, 255, "Reach: Define the reach distance from 7 to 255 blocks");
}

BlockReach::~BlockReach() {
}

const char* BlockReach::getModuleName() {
	return "BlockReach";
}
