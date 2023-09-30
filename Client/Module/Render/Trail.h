#pragma once
#include "../Module.h"

class Trail : public Module {
public:
	SettingEnum mode = SettingEnum(this);
	int trailDuration = 45;
	int trailDelay = 1;
	int countDelay = 0;
	bool Rainbow = true;

	Trail();
	~Trail();

	struct CircleStatus {
		Vec3 pos;
		int duration;
	};
	std::vector<CircleStatus> Circles;

	virtual const char* getModuleName() override;
	virtual std::string getModSettings() override;
	virtual void onPostRender(MinecraftUIRenderContext* renderCtx) override;
	virtual void onTick(GameMode* gm) override;
};