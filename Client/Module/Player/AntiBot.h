#pragma once
#include "../Module.h"
class AntiBot : public Module {
private:
	bool hitboxCheck = true;
	bool nameCheck = false;
	bool invisibleCheck = true;
	bool entityIdCheck = true;
	bool otherCheck = true;
	bool extraCheck = false;
	bool playerCheck = true;

public:
	AntiBot::AntiBot() : Module(0, Category::PLAYER, "filter bots and non player char") {
		registerBoolSetting("Hitbox Check", &hitboxCheck, hitboxCheck);
		registerBoolSetting("Invisible Check", &invisibleCheck, invisibleCheck);
		registerBoolSetting("EntityID Check", &entityIdCheck, entityIdCheck);
		registerBoolSetting("Other Check", &otherCheck, otherCheck);
		registerBoolSetting("Extra Check", &extraCheck, extraCheck);
		registerBoolSetting("Player Check", &playerCheck, playerCheck);
	}
	~AntiBot(){};

	inline bool isHitboxCheckEnabled() {
		return hitboxCheck && this->isEnabled();
	}
	inline bool isNameCheckEnabled() {
		return false;
	}
	inline bool isInvisibleCheckEnabled() {
		return invisibleCheck && this->isEnabled();
	}
	inline bool isEntityIdCheckEnabled() {
		return entityIdCheck && this->isEnabled();
	}
	inline bool isOtherCheckEnabled() {
		return otherCheck && this->isEnabled();
	}
	inline bool isExtraCheckEnabled() {
		return this->extraCheck && this->isEnabled();
	}
	inline bool isPlayerCheckEnabled() {
		return playerCheck && isEnabled();
	}

	virtual const char* getModuleName() override {
		return "AntiBot";
	}
};