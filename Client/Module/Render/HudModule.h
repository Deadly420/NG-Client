#pragma once

#include "../Module.h"

class HudModule : public Module {
public:
	HudModule();
	~HudModule();

	bool clickToggle = true;
	bool watermark = true;
	bool coordinates = false;
	bool keybinds = true;
	bool displayArmor = true;
	bool keystrokes = true;
	bool fps = true;
	bool cps = true;
	bool alwaysShow = false;

	float scale = 1.f;

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
};
