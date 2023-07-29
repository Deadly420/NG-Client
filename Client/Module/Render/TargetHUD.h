#pragma once
#include "../../../Client/Module/Module.h"
#include "../../../Utils/Target.h"
#include "../ModuleManager.h"

class TargetHUD : public Module {
public:
	SettingEnum mode = this;
	bool hurttime = false;
	int targethud = 0;
	int counter = 0;
	float positionX = 10;
	float positionY = 40;
	bool animation = true;

	TargetHUD();
	~TargetHUD();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
};