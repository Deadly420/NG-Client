#include "MoveUtils.h"

void MoveUtil::freeze(Vec3 initPos, bool damageTime) {
	// execute in something that ticks fast, like onPlayerTick
	// initPos is the players pos in onEnable

	auto player = Game.getLocalPlayer();
	if (player != nullptr) {
		if (!(player->damageTime > 1 && damageTime)) {
			player->setPos(initPos);
			fullStop(false);
		}
	}
}

void MoveUtil::fullStop(bool damageTime) {
	auto player = Game.getLocalPlayer();
	if (player != nullptr) {
		if (!(player->damageTime > 1 && damageTime)) {
			player->entityLocation->velocity.x = 0.f;
			player->entityLocation->velocity.y = 0.f;
			player->entityLocation->velocity.z = 0.f;
		}
	}
}

void MoveUtil::stop(bool damageTime) {
	auto player = Game.getLocalPlayer();
	if (player != nullptr) {
		if (!(player->damageTime > 1 && damageTime)) {
			player->entityLocation->velocity.x = 0.f;
			player->entityLocation->velocity.z = 0.f;
		}
	}
}

void MoveUtil::setSpeed(float speed) {
	MoveInputHandler* input = Game.getClientInstance()->getMoveTurnInput();
	auto player = Game.getLocalPlayer();
	float calcYaw = (player->getActorRotationComponent()->rot.y + 90) * (PI / 180);
	float c = cos(calcYaw);
	float s = sin(calcYaw);

	Vec2 moveVec2D = {input->forwardMovement, -input->sideMovement};
	moveVec2D = {moveVec2D.x * c - moveVec2D.y * s, moveVec2D.x * s + moveVec2D.y * c};
	Vec3 moveVec;

	moveVec.x = moveVec2D.x * speed;
	moveVec.y = player->entityLocation->velocity.y;
	moveVec.z = moveVec2D.y * speed;
	player->lerpMotion(moveVec);
}

bool MoveUtil::keyPressed() {
	MoveInputHandler* input = Game.getClientInstance()->getMoveTurnInput();
	Vec2 movement = {input->forwardMovement, -input->sideMovement};
	return movement.magnitude() > 0.f;
}

bool MoveUtil::isMoving() {
	return Game.getLocalPlayer()->entityLocation->velocity.magnitudexz() > 0.05f;
}
float getTicksPerSecond() {
	if (Game.getLocalPlayer() != nullptr) {
		Vec3 targetPos = *Game.getLocalPlayer()->getPos();
		Vec3 targetPosOld = *Game.getLocalPlayer()->getPosOld();
		float hVel = sqrtf(((targetPos.x - targetPosOld.x) * (targetPos.x - targetPosOld.x)) + ((targetPos.z - targetPosOld.z) * (targetPos.z - targetPosOld.z)));
		return hVel;
	}
}