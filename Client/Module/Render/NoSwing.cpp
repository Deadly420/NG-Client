#include "NoSwing.h"

NoSwing::NoSwing() : Module(0x0, Category::PLAYER, "Disable arm swing animation (Server cancels the AnimatePacket being sent)") {
	registerBoolSetting("Server", &server, server, "Enable or disable the server feature");
}

NoSwing::~NoSwing() {}

const char* NoSwing::getModuleName() {
	return ("NoSwing");
}