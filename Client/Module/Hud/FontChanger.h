#pragma once
#include "../Module.h"

class FontChanger : public Module {
public:
	SettingEnum Fonts = SettingEnum(this);
	FontChanger();
	~FontChanger();

	// Inherited via Module
	virtual const char* getModuleName() override;
};