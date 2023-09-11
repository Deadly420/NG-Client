#include "EntityFly.h"

EntityFly::EntityFly() : Module(0x0, Category::ENTITY, "Fly will riding entities, use up and down arrows to move!") {
	registerFloatSetting("Horizontal Speed", &speed2, speed2, 0.01f, 10.00f);  // allows you to ajust your speed.
	registerFloatSetting("Vertical Speed", &upspeed, upspeed, 0.50f, 10.00f);  // allows you to ajust your speed
}

EntityFly::~EntityFly() {
}

const char* EntityFly::getModuleName() {
	return ("EntityFly");
}
static std::vector<Entity*> targetJoe;
void findJoe(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	int entityTypeId = currentEntity->getEntityTypeId();
	// PIG: 4876, HORSE:2118423, DONKEY: 2118424, MULE: 2118425, BOAT: 90
	if (entityTypeId != 4876 && entityTypeId != 2118423 && entityTypeId != 2118424 && entityTypeId != 2118425 && entityTypeId != 90)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 3) {
		targetJoe.push_back(currentEntity);
	}
}

void EntityFly::onTick(GameMode* gm) {
	targetJoe.clear();
	Game.forEachEntity(findJoe);

	if (!targetJoe.empty()) {
		// keeps you in the air
		glideModEffective = glideMod;
		targetJoe[0]->entityLocation->velocity.y = glideModEffective;
		GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();

		if (Game.canUseMoveKeys() && !targetJoe.empty()) {
			if (GameData::isKeyDown(VK_DOWN)) {
				targetJoe[0]->entityLocation->velocity.y -= upspeed;
			}
			if (GameData::isKeyDown(VK_UP)) {
				targetJoe[0]->entityLocation->velocity.y += upspeed;
			}
		}
	}
}

void EntityFly::onMove(MoveInputHandler* input) {
	targetJoe.clear();
	Game.forEachEntity(findJoe);

	if (!targetJoe.empty()) {
		float yaw = targetJoe[0]->getActorHeadRotationComponent()->rot.y;
		if (targetJoe[0] && targetJoe[0] == nullptr) return;
		if (targetJoe[0]->isSneaking())
			return;
		Vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (input->right) {
			yaw += 90.f;
			if (input->forward)
				yaw -= 20.f;

			else if (input->backward)
				yaw += 45.f;
		}
		if (input->left) {
			yaw -= 90.f;
			if (input->forward)
				yaw += 45.f;
			else if (input->backward)
				yaw -= 45.f;
		}

		if (input->backward && !input->left && !input->right)
			yaw += 180.f;

		float calcYaw = (yaw + 90.f) * (PI / 180.f);
		Vec3 moveVec;
		moveVec.x = cos(calcYaw) * speed2;
		moveVec.y = targetJoe[0]->entityLocation->velocity.y;
		moveVec.z = sin(calcYaw) * speed2;
		if (pressed) targetJoe[0]->lerpMotion(moveVec);
		if (!pressed) {
			targetJoe[0]->entityLocation->velocity.x = 0;
			targetJoe[0]->entityLocation->velocity.z = 0;
		}
	}
}