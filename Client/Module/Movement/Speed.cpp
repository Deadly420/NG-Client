#include "Speed.h"

Speed::Speed() : Module(0x0, Category::MOVEMENT, "Speed up!") {
	registerFloatSetting("Speed", &speed, 1, 0.01f, 3.f, "Speed: Adjust the speed from 0.01 to 3.0");
}

Speed::~Speed() {}

const char* Speed::getModuleName() {
	return "Speed";
}

void Speed::onTick(GameMode* gm) {
	if (auto localPlayer = Game.getLocalPlayer(); localPlayer != nullptr) {
		if (auto speedAdr = reinterpret_cast<float*>(localPlayer->getSpeed() + 0x84); speedAdr != nullptr) {
			*speedAdr = speed;
		}
	}
}

void Speed::onEnable() {
	if (auto localPlayer = Game.getLocalPlayer(); localPlayer != nullptr) {
		origSpeed = *reinterpret_cast<float*>(localPlayer->getSpeed() + 0x84);
	} else {
		setEnabled(false);
	}
}

void Speed::onDisable() {
	if (auto localPlayer = Game.getLocalPlayer(); localPlayer != nullptr) {
		if (auto speedAdr = reinterpret_cast<float*>(localPlayer->getSpeed() + 0x84); speedAdr != nullptr) {
			*speedAdr = origSpeed;
		}
	}
}