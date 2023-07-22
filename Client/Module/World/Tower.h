#pragma once

#include "../Module.h"

class Tower : public Module {
private:
	float motion = 0.5f;
	bool tryTower(Vector3 blockBelow);

public:
	Tower();
	~Tower();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
};
