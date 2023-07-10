#pragma once

#include "Module.h"

class Teams : public Module {
private:
	bool alliedCheck = false;
	bool colorCheck = true;

public:
	Teams();
	~Teams();

	bool isAlliedCheckEnabled() { return isEnabled() && alliedCheck; };
	bool isColorCheckEnabled() { return isEnabled() && colorCheck; };

	// Inherited via Module
	virtual const char* getModuleName() override;
};
