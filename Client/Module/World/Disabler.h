#pragma once

#include "../Module.h"

class Disabler : public Module {
public:
	int counter = 1;
	SettingEnum disablerMode = this;

	virtual const char* getModuleName();
	virtual std::string getModSettings() override;
	virtual void onMove(MoveInputHandler* input) override;
	void onEnable();
	void onTick(GameMode* gm);
	void onSendPacket(Packet* packet) override;

	Disabler();

	// virtual void onSendPacket(Packet* packet) override;
	inline std::vector<MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
	std::vector<MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;
};