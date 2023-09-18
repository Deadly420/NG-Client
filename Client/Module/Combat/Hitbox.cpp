#include "Hitbox.h"

Hitbox::Hitbox() : Module(0x0, Category::COMBAT, "Increase an entitys hitbox size.") {
	registerFloatSetting("Height", &height, height, 1.8f, 10, "");
	registerFloatSetting("Width", &width, width, 0.6f, 10, "");
}

Hitbox::~Hitbox() {
}

const char* Hitbox::getModuleName() {
	return ("Hitbox");
}

void findTarget(Entity* currentEntity, bool isRegularEntity) {
	static auto hitboxMod = moduleMgr->getModule<Hitbox>();

	// Skip the local player
	if (currentEntity == Game.getLocalPlayer()) {
		return;
	}

	// Skip if currentEntity is null or not alive, or if damageTime exceeds the threshold
	if (currentEntity == nullptr || !currentEntity->isAlive() || currentEntity->damageTime >= 7) {
		return;
	}

	// Check if currentEntity is a valid target
	if (!Target::isValidTarget(currentEntity)) {
		return;
	}

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	// Adjust the entity's AABB if it is within the range
	if (dist < hitboxMod->range) {
		currentEntity->aabb->width = hitboxMod->width;
		currentEntity->aabb->height = hitboxMod->height;
	}
}


void Hitbox::onTick(GameMode* gm) {
	Game.forEachEntity(findTarget);
}
