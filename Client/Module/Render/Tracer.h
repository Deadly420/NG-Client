#pragma once

#include "../Module.h"

class Tracer : public Module {
public:
	Tracer();
	~Tracer();

	// Inherited via Module
	virtual const char* getModuleName() override;
	void onPreRender(MinecraftUIRenderContext* renderCtx) override;
};