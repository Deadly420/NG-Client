#include "Disabler.h"

#include <chrono>
#include <queue>

Disabler::Disabler() : Module(0x0, Category::WORLD, "Disabler for servers") {
	registerEnumSetting("Disabler Types", &disablerMode, 0, "Disabler Types: Choose a disabler type from the options");
	disablerMode.addEntry("Hive", 0);
	disablerMode.addEntry("CubeCraft", 1);
	disablerMode.addEntry("Mineplex", 2);
}

std::queue<std::pair<NetworkLatencyPacket, unsigned __int64> > latencyPacketQueue;
std::queue<std::pair<NetworkLatencyPacket, unsigned __int64> > emptyPacketQueue;

bool sendingEpicThingy = false;

const char* Disabler::getModuleName() {
	return ("Disabler");
}
std::string Disabler::getModSettings() {
	return disablerMode.GetSelectedEntry().GetName();
}

void Disabler::onEnable() {
	latencyPacketQueue = emptyPacketQueue;
}

void Disabler::onTick(GameMode* gm) {
	if (disablerMode.selected == 0) {
		unsigned __int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		while (!latencyPacketQueue.empty() && now - latencyPacketQueue.front().second >= 1000) {
			NetworkLatencyPacket packetToSend = latencyPacketQueue.front().first;
			sendingEpicThingy = true;
			Game.getClientInstance()->loopbackPacketSender->sendToServer(&packetToSend);
			sendingEpicThingy = false;
			latencyPacketQueue.pop();
		}
	}
	if (disablerMode.selected == 2) {
		MovePlayerPacket onG(Game.getLocalPlayer(), *Game.getLocalPlayer()->getPos());
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&onG);
	}
}

void Disabler::onMove(MoveInputHandler* input) {
}

void Disabler::onSendPacket(Packet* packet) {
	if (packet->isInstanceOf<NetworkLatencyPacket>()) {
		if (sendingEpicThingy == false) {
			NetworkLatencyPacket* currentPacket = (NetworkLatencyPacket*)packet;
			unsigned __int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			if (disablerMode.selected == 0) latencyPacketQueue.push({*currentPacket, now});  // Only push to vector if it's Hive mode
			currentPacket->timeStamp = 69420;
		}
	} else if (disablerMode.selected == 1 && packet->isInstanceOf<PlayerAuthInputPacket>()) {
		PlayerAuthInputPacket* pkt = (PlayerAuthInputPacket*)packet;
		pkt->velocity = Vec3(0, 0, 0);
	}
}