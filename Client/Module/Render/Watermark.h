#pragma once
#include "../Module.h"

class Watermark : public Module {
public:
	SettingEnum watermark;
	float opacity = 0.f;
	bool rgb = true;
	Watermark();
	~Watermark();

	virtual const char* getModuleName() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
};