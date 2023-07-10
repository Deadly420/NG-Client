#pragma once

#include "Module.h"

class PacketLogger : public Module {
public:
	SettingEnum packetType;
	bool packetadd;
	bool authchunk = false;
	bool setTitle = false;
	SettingEnum addressType;
	PacketLogger();
	~PacketLogger();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onSendPacket(Packet* packet) override;
	virtual void onSendClientPacket(Packet* packet) override;
};