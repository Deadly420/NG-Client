#pragma once

#include "../Module.h"

class ClickGuiMod : public Module {
public:
	int Opacity = 0;
	bool showTooltips = true;
	bool resetOnInject = true;
	bool resetOnOpen = true;
	bool resetStartPos = true;
	SettingEnum mode = SettingEnum(this);

	ClickGuiMod();
	~ClickGuiMod();

	// Inherited via Module
	virtual void onEnable() override;
	virtual void onDisable() override;
	virtual bool allowAutoStart() override;
	virtual const char* getModuleName() override;
	virtual void onLoadConfig(void* conf) override;
	virtual void onSaveConfig(void* conf) override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
};
