#pragma once
#include "../Module.h"

class Arraylist : public Module {
public:
	SettingEnum mode = SettingEnum(this);

	int X = static_cast<int>(Game.getClientInstance()->getGuiData()->windowSize.x);
	int Y = 1;
	float opacity = 0.6f;
	float cycleSpeed = 3.f;
	float saturation = 1.f;
	bool bottom = false;
	bool modes = true;
	float scale = 1.f;

	Arraylist();
	~Arraylist();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual std::string getModSettings() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
};