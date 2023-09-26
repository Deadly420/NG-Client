#pragma once
#include "../Module.h"
#include "../../Manager/ModuleManager.h"
class Blink : public Module {
public:
	std::vector<MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
	inline std::vector<MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };

	Blink() : Module(0x0, Category::PLAYER, "Stops you from sending packets and then sends them in a bunch") {};

	~Blink() {
		if (!Game.canUseMoveKeys()) return;
		getMovePlayerPacketHolder()->clear();
		getPlayerAuthInputPacketHolder()->clear();
	};

	bool isFlashMode() {
		return true;
	}

	virtual const char* getModuleName() override {
		return "Blink";
	}
};