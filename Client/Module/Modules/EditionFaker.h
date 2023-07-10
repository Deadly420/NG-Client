#pragma once

#include "Module.h"

class EditionFaker : public Module {
public:
	SettingEnum edition = SettingEnum(this);
	
	EditionFaker();
	~EditionFaker();

	int getFakedEditon();

	// Inherited via Module
	virtual const char* getModuleName() override;
};
