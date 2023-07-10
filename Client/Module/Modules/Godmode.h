#pragma once

#include "Module.h"

class Godmode : public Module {
private:
	int regendelay = 5;
	int regenvalue = 5;
	int delay = 0;

public:
	Godmode();
	~Godmode();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onSendPacket(Packet* p) override;
};
