#pragma once
#include "../Module.h"
#include "../../Manager/ModuleManager.h"

class Breaker : public Module {
public:
	Breaker();
	~Breaker();
	float range = 1;
	int delay = 1;
	int Odelay = 0;
	int delayTimer = 0;
	int mineDelay = 0;
	int mineDelayTimer = 0;
	bool beds = false;
	bool eggs = false;
	bool cakes = false;
	bool treasures = false;
	bool chests = true;
	bool echests = true;
	bool redstone = false;
	bool diamond = false;
	bool gOre = false;
	bool lOre = false;
	bool iron = false;
	bool emerald = false;
	bool bypass = false;
	bool rots = true;
	Vec3i blockPos;
	bool noSwing = false;
	bool destroy;

	// Inherited via Module
	virtual const char* getModuleName() override;
	virtual void onTick(GameMode* gm) override;
	virtual void onPlayerTick(Player* plr) override;
	virtual void onLevelRender() override;
	virtual void onSendPacket(Packet* packet) override;
};
