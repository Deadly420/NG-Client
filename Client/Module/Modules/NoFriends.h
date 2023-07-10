#pragma once

#include "Module.h"

class NoFriends : public Module {
public:
	NoFriends();
	~NoFriends();

	// Inherited via Module
	virtual const char* getModuleName() override;
};
