#include "Desync.h"
#include "../../../Utils/TimerUtil.h"

using namespace std;

Desync::Desync() : Module(0, Category::MISC, "NetSkip but better") {
	DelayMode.addEntry(EnumEntry("Pos", 0));  //.addEntry(EnumEntry("Packet", 1));
	registerEnumSetting("DelayMode", &DelayMode, 0, "Desync Mode");
	registerBoolSetting("Desync", &desync, desync, "Desync Your Pos");
	registerIntSetting("DesyncMS", &desyncMs, desyncMs, 0, 5000, "Desync Value");
}

Desync::~Desync() {
}

const char* Desync::getModuleName() {
	return "Desync";
}

void Desync::onEnable() {
	desyncLastMS = TimerUtil::getCurrentMs();
}

void Desync::onTick(GameMode* gm) {
	if (desync) {
		doDesync = true;
	} else {
		doDesync = false;
	}
}

void Desync::onDisable() {
	doDesync = false;
}