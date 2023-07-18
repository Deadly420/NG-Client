#pragma once
#include "../Module.h"
#include "../ModuleManager.h"

class Bhop : public Module {
public:
	float speed = 0.90f;
	bool hive = false;
	int timer = 20;
	int height = 4;
	int speedIndexThingyForHive = 13;
	double epicHiveSpeedArrayThingy[13] = {
		0.325,
		0.32,
		0.3,
		0.28,
		0.26,
		0.24,
		0.22,
		0.2,
		0.18,
		0.16,
		0.14,
		0.12,
		0.1};

	MoveInputHandler* yes;
	MoveInputHandler cachedInput;
	Bhop() : Module(0x0, Category::MOVEMENT, "Hop around like a bunny!") {
		registerBoolSetting("Hive", &hive, hive);
		registerFloatSetting("Speed", &speed, speed, 0.9f, 2.f);
		registerIntSetting("Height", &height, height, 1, 8);
		registerIntSetting("Timer", &timer, timer, 20, 50);
	}
	~Bhop(){};

	virtual const char* getModuleName() override {
		return ("Bhop");
	}

	std::vector<C_MovePlayerPacket*> MovePlayerPacketHolder;
	inline std::vector<C_MovePlayerPacket*>* getMovePlayerPacketHolder() { return &MovePlayerPacketHolder; };
	// Inherited via Module
	virtual void onTick(GameMode* gm) override {
		Game.getClientInstance()->minecraft->setTimerSpeed(static_cast<float>(timer));
	}
	virtual void onMove(MoveInputHandler* input) override;
	virtual void onDisable() override { Game.getClientInstance()->minecraft->setTimerSpeed(20.f); }
	virtual void onEnable() override { speedIndexThingyForHive = 13; }
};