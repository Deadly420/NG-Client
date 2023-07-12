#pragma once

#include "../Module.h"

class Crasher : public Module {
public:
	Crasher();
	~Crasher();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onSendPacket(Packet* packet) override;
	virtual void onEnable() override;
	virtual void onTick(GameMode* gm) override;
};
