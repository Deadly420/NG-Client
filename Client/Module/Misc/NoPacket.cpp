#include "NoPacket.h"

NoPacket::NoPacket() : Module(0x0, Category::MISC, "Prevents you from sending InventoryTransaction packets.") {
}

NoPacket::~NoPacket() {
}

const char* NoPacket::getModuleName() {
	return ("NoPacket");
}
bool NoPacket::allowAutoStart() {
	return false;
}
void NoPacket::onEnable() {
	if(!Game.isInGame())
		setEnabled(false);
}
