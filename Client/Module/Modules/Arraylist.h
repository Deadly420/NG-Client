#pragma once
#include "Module.h"

class Arraylist : public Module {
public:
	SettingEnum mode = SettingEnum(this);

	int X = static_cast<int>(Game.getClientInstance()->getGuiData()->windowSize.x);
	int Y = 1;
	float opacity = 0.6f;
	bool bottom = false;
	bool keybinds = false;
	bool modes = true;

	Arraylist();
	~Arraylist();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
};