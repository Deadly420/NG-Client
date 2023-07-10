#pragma once

#include "Module.h"
#include "../../../Utils/DrawUtils.h"

class Compass : public Module {
private:
	float opacity = 0.5;
	int range = 90;
	bool showWaypoints = true;
	void drawCenteredText(Vec2 pos, std::string text, float size, float textOpacity = 1);

public:
	Compass();
	~Compass();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
};
