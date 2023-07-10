#pragma once

#include "Module.h"

class Blink : public Module {
private:
	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	std::vector<PlayerAuthInputPacket*> PlayerAuthInputPacketHolder;

public:
	Blink();
	~Blink();

	// Inherited via Module
	virtual void onTick(GameMode* gm) override;
	virtual const char* getModuleName() override;

	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	inline std::vector<PlayerAuthInputPacket*>* getPlayerAuthInputPacketHolder() { return &PlayerAuthInputPacketHolder; };
};
