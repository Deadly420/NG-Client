#pragma once

#include "../Module.h"

class NoPacket : public Module {
public:
	NoPacket();
	~NoPacket();

	// Inherited via Module
	virtual const char* getModuleName() override;
	bool allowAutoStart() override;
	void onEnable() override;
};
