#pragma once

#include "../Module.h"

class Derp : public Module {
private:
	int counter = 0;
	bool epicStroke = false;
	bool packetMode = false;

public:
	Derp();
	~Derp();

	// Inherited via Module
	virtual void onPlayerTick(Player* player) override;
	virtual const char* getModuleName() override;
};
