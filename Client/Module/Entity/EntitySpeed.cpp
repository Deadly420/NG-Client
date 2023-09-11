#include "EntitySpeed.h"

EntitySpeed::EntitySpeed() : Module(0x0, Category::ENTITY, "Makes rideable entities faster when riding them") {
	registerFloatSetting("Horizontal Speed", &speed2, speed2, 0.01f, 10.00f);  // allows you to ajust your speed.
}

EntitySpeed::~EntitySpeed() {
}

const char* EntitySpeed::getModuleName() {
	return ("EntitySpeed");
}
static std::vector<Entity*> targetDeez;
void findDeez(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	int entityTypeId = currentEntity->getEntityTypeId();
	// PIG: 4876, HORSE:2118423, DONKEY: 2118424, MULE: 2118425, BOAT: 90
	if (entityTypeId != 4876 && entityTypeId != 2118423 && entityTypeId != 2118424 && entityTypeId != 2118425 && entityTypeId != 90)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 3) {
		targetDeez.push_back(currentEntity);
	}
}

void EntitySpeed::onTick(GameMode* gm) {
	targetDeez.clear();
	Game.forEachEntity(findDeez);

	if (!targetDeez.empty()) {
		GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();

		if (input == nullptr)
			return;

		float speed = speed2;
		float yaw = targetDeez[0]->getActorHeadRotationComponent()->rot.y;

		if (GameData::isKeyDown(*input->spaceBarKey) && targetDeez[0]->isOnGround())
			targetDeez[0]->jumpFromGround();

		if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->backKey))
			return;

		bool keyPressed = false;

		if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
			yaw += 45.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->forwardKey) && GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
			yaw -= 45.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->backKey) && GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
			yaw += 135.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->backKey) && GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
			yaw -= 135.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->forwardKey)) {
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->backKey)) {
			yaw += 180.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->rightKey) && !GameData::isKeyDown(*input->leftKey)) {
			yaw += 90.f;
			keyPressed = true;
		} else if (GameData::isKeyDown(*input->leftKey) && !GameData::isKeyDown(*input->rightKey)) {
			yaw -= 90.f;
			keyPressed = true;
		}

		if (yaw >= 180)
			yaw -= 360.f;

		float calcYaw = (yaw + 90) * (PI / 180);
		Vec3 moveVec;
		moveVec.x = cos(calcYaw) * speed;
		moveVec.y = targetDeez[0]->entityLocation->velocity.y;
		moveVec.z = sin(calcYaw) * speed;

		if (keyPressed) {
			targetDeez[0]->lerpMotion(moveVec);
			keyPressed = false;
		}
	}
}
