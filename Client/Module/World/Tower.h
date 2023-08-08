#pragma once

#include "../Module.h"

class Tower : public Module {
private:
	float motion = 0.5f;
	bool hive = false;
	bool tryTower(Vec3 blockBelow);

public:
	Tower();
	~Tower();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onMove(MoveInputHandler* input) override;
	virtual void onDisable() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
};
