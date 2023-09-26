#pragma once

#include "../Module.h"
#include "../../Manager/ModuleManager.h"
#include "../../../Utils/Target.h"

class Killaura : public Module
{
private:
	bool isMulti = true;
	int delay = 0;
	int minD = 0;
	int maxD = 20;
	bool autoweapon = false;
	void findWeapon();
	bool silent = true;

public:
	bool rotations = false;
	bool targetListEmpty = false;
	Vec2 angle;
	bool targetMobs = false;
	bool hurttime = true;
	float range = 6;


	Killaura();
	~Killaura();

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onEnable() override;
	virtual void onSendPacket(Packet* packet) override;
};