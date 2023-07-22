#pragma once

#include "../Module.h"
#include "../../../SDK/Camera.h"

class Freecam : public Module {
public:
	float speed = 0.325f;
	float yaw = 0;
	Vector2 initialViewAngles;
	Camera* camera = nullptr;
	bool keyPressed = false;

	Freecam();
	~Freecam();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onPreRender(MinecraftUIRenderContext* rcx) override;
	virtual void onEnable() override;
	virtual void onDisable() override;
};
