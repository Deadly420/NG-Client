#pragma once
#include "../Module.h"

class Arraylist : public Module {
public:
	SettingEnum mode = SettingEnum(this);

	int X = static_cast<int>(Game.getClientInstance()->getGuiData()->windowSize.x);
	int Y = 1;
	float padding = 0.4f;  // Initial padding value
	float scale = 1.0f;    // Initial scale value
	float opacity = 0.6f;
	float cycleSpeed = 3.f;
	float saturation = 1.f;
	bool modes = true;

	Arraylist();
	~Arraylist();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual std::string getModSettings() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
};