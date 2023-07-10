#pragma once

#include "Module.h"

class Criticals : public Module {
public:
	bool test = false;
	Criticals();
	~Criticals();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onSendPacket(Packet* packet) override;
};
