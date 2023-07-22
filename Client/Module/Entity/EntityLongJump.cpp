#include "EntityLongJump.h"

EntityLongJump::EntityLongJump() : Module(0x0, Category::ENTITY, "even funnier") {
	registerFloatSetting("Speed", &speed, speed, 0.05f, 1.5f);
	registerFloatSetting("Up Value", &upVal, upVal, 0.05f, 1.5f);
}

EntityLongJump::~EntityLongJump() {
}

const char* EntityLongJump::getModuleName() {
	return ("EntityLongJump");
}
static std::vector<Entity*> targetOrphan;
void findOrphan(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	if (currentEntity->getEntityTypeId() != 90 && currentEntity->getEntityTypeId() != 2186010 && currentEntity->getEntityTypeId() != 2118423 && currentEntity->getEntityTypeId() != 4876 && currentEntity->getEntityTypeId() != 2118424)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 3) {
		targetOrphan.push_back(currentEntity);
	}
}
void EntityLongJump::onMove(MoveInputHandler* input) {
	targetOrphan.clear();
	Game.forEachEntity(findOrphan);

	if (!targetOrphan.empty()) {
		auto player = targetOrphan[0];
		if (player == nullptr) return;

		if (player->isInLava() == 1 || player->isInWater() == 1)
			return;

		if (player->isSneaking())
			return;

		Vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (player->onGround && pressed)
			player->jumpFromGround();

		float calcYaw = (player->yaw + 90) * (PI / 180);
		Vec3 moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
		if (player->onGround && pressed && !input->isJumping)
			player->velocity.y += upVal;
	}
}