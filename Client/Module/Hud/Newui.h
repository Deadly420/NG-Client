#pragma once
#include "../Module.h"

class NewUI : public Module {
public:
	NewUI();
	~NewUI();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onImGuiRender() override;
	virtual void onEnable() override;
	static void onKeyUpdate(int key, bool isDown);
};