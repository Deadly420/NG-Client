#pragma once
#include "../Module.h"

class NewUI : public Module {
public:
	int Opacity = 0;
	NewUI();
	~NewUI();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onImGuiRender() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
	static void renderTooltip(std::string* text);
	virtual void onDisable() override;
	virtual void onEnable() override;
	static void onKeyUpdate(int key, bool isDown);
};