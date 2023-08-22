#pragma once
#include "../Module.h"
class KeyStrokes : public Module {
public:
	KeyStrokes();
	~KeyStrokes();

	float keystrokesX = 9.f;
	float keystrokesY = 9.f;
	float opacity = true;
	bool keybindsRGB = true;
	bool flip = false;

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onPreRender(MinecraftUIRenderContext* renderCtx) override;
	static void drawKeystroke(char key, Vec2 pos);
	static void drawLeftMouseKeystroke(Vec2 pos);
	static void drawRightMouseKeystroke(Vec2 pos);
	static void CPS(Vec2 pos);
};