#pragma once

#include "../Module.h"

class Tracer : public Module {
public:
	SettingEnum type = SettingEnum(this);
	Tracer();
	~Tracer();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual std::string getModSettings() override;
	void onPreRender(MinecraftUIRenderContext* renderCtx) override;
};