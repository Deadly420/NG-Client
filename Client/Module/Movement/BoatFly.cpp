#include "BoatFly.h"

BoatFly::BoatFly() : Module(0x0, Category::MOVEMENT, "Fly A Boat (UP Arrow, Down Arrow)") {
	registerFloatSetting("Horizontal Speed", &speed2, speed2, 0.01f, 10.00f);
	registerFloatSetting("Vertical Speed", &upspeed, upspeed, 0.50f, 10.00f);
}

BoatFly::~BoatFly() {
}

const char* BoatFly::getModuleName() {
	return ("BoatFly");
}

static std::vector<Entity*> targetJoe;
void findhoe(Entity* currentEntity, bool isRegularEntity) {
	if (!currentEntity || isRegularEntity) {
		return;
	}

	int entityTypeId = currentEntity->getEntityTypeId();
	if (entityTypeId != 90) {
		return;
	}

	Vec3 playerPos = *(Game.getLocalPlayer()->getPos());
	Vec3 entityPos = *(currentEntity->getPos());

	float dist = entityPos.dist(playerPos);

	if (dist < 3) {
		targetJoe.push_back(currentEntity);
	}
}

void BoatFly::onTick(GameMode* gm) {
	if (targetJoe.empty()) {
		return;
	}

	Entity* joe = targetJoe[0];
	joe->velocity.y = 0;

	GameSettingsInput* input = Game.getClientInstance()->getGameSettingsInput();
	bool canUseMoveKeys = Game.canUseMoveKeys();

	if (canUseMoveKeys) {
		bool DownKey = GameData::isKeyDown(VK_DOWN);
		bool UpKey = GameData::isKeyDown(VK_UP);

		if (DownKey) {
			joe->velocity.y -= upspeed;
		}
		if (UpKey) {
			joe->velocity.y += upspeed;
		}
	}
}


void BoatFly::onMove(MoveInputHandler* input) {
	if (targetJoe.empty()) {
		return;
	}

	Entity* joe = targetJoe[0];
	if (!joe || joe->isSneaking()) {
		return;
	}

	float newYaw = joe->yaw;

	if (input->right) {
		newYaw += 90.f;
		if (input->forward) {
			newYaw -= 20.f;
		} else if (input->backward) {
			newYaw += 45.f;
		}
	} else if (input->left) {
		newYaw -= 90.f;
		if (input->forward) {
			newYaw += 45.f;
		} else if (input->backward) {
			newYaw -= 45.f;
		}
	} else if (input->backward && !input->left && !input->right) {
		newYaw += 180.f;
	}

	float calcYaw = (newYaw + 90.f) * (PI / 180.f);
	float cosCalcYaw = cos(calcYaw);
	float sinCalcYaw = sin(calcYaw);

	Vec3 moveVec;
	moveVec.x = cosCalcYaw * speed2;
	moveVec.y = joe->velocity.y;
	moveVec.z = sinCalcYaw * speed2;

	bool pressed = (input->forwardMovement * input->forwardMovement +
					input->sideMovement * input->sideMovement) > 0.01f;

	if (pressed) {
		joe->lerpMotion(moveVec);
	} else {
		joe->velocity.x = 0;
		joe->velocity.z = 0;
	}
}