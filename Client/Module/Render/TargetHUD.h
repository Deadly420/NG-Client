#pragma once
#include "../../../Client/Module/Module.h"
#include "../../../Utils/Target.h"
#include "../../Manager/ModuleManager.h"

class TargetHUD : public Module {
public:
	TargetHUD();
	~TargetHUD();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onImGuiRender() override;
	// virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
};