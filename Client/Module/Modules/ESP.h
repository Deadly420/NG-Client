#pragma once

#include "Module.h"
#include "../ModuleManager.h"

class ESP : public Module {
public:
	bool isMobEsp = false;
	bool doRainbow = true;
	bool is2d = false;
	ESP();
	~ESP();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
};
