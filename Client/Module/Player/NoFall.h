#pragma once

#include "../../../Utils/DrawUtils.h"
#include "../Module.h"

class NoFall : public Module {
public:
	SettingEnum mode = SettingEnum(this);
	Vec3 closestGround;
	bool isOverVoid();
	NoFall();
	~NoFall();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onSendPacket(Packet* packet) override;
	virtual void onTick(GameMode* gm) override;
};