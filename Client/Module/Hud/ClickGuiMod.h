#pragma once

#include "../Module.h"

class ClickGuiMod : public Module {
public:
	ClickGuiMod();
	~ClickGuiMod();

	int Opacity = 0;
	bool showTooltips = true;

	// Inherited via Module
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
	virtual const char* getModuleName() override;
	virtual void onDisable() override;
	virtual void onEnable() override;
	virtual bool allowAutoStart() override;
	virtual void onLoadConfig(void* conf) override;
	virtual void onSaveConfig(void* conf) override;
};
