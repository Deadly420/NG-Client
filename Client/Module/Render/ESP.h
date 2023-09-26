#pragma once

#include "../Module.h"
#include "../../Manager/ModuleManager.h"

class ESP : public Module {
public:
	SettingEnum mode = this;
	bool isMobEsp = false;
	bool doRainbow = true;
	bool item = false;

	ESP();
	~ESP();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual std::string getModSettings() override;
	virtual void onEnable() override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
};