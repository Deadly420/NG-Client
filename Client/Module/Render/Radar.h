#pragma once

#include "../Module.h"
#include "../../../Utils/DrawUtils.h"

class Radar : public Module {
public:
	Radar();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
};
