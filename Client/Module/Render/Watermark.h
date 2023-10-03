#pragma once
#include "../Module.h"

class Watermark : public Module {
public:
	bool ImGui = true;
	SettingEnum watermark;
	float opacity = 0.f;
	bool rgb = true;
	Watermark();
	~Watermark();

	virtual const char* getModuleName() override;
	virtual void onImGuiRender() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
};