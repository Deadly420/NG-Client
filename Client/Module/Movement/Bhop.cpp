#include "Bhop.h"

#include "../../../Utils/HMath.h"

Bhop::Bhop() : Module(0, Category::MOVEMENT, "Hop around like a bunny!") {
	registerFloatSetting("Speed", &speed, speed, 0.1f, 0.8f, "Speed: Set the speed from 0.1 to 0.8");
	registerBoolSetting("flareon", &flareon, flareon, "flareon: Enable or disable the flareon feature");
}

Bhop::~Bhop() {
}

const char* Bhop::getModuleName() {
	return "Bhop";
}

void Bhop::onMove(MoveInputHandler* input) {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	if (player->isInWater())
		return;

	if (Game.getClientInstance()->getMoveTurnInput()->isSneakDown)
		return;

	Vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;

	float calcYaw = (player->getActorHeadRotationComponent()->rot.y + 90) * (PI / 180);
	Vec3 moveVec;
	float c = cos(calcYaw);
	float s = sin(calcYaw);
	moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};

	if (flareon) {
		player->getMaxAutoStepComponent()->stepHeight = 0.f;
		static bool useVelocity = false;
		if (0.4000000059604645 >= 0.385) {
			if (player->getMovementProxy()->isOnGround() && pressed) player->jumpFromGround();
			useVelocity = false;
		} else
			useVelocity = true;

		speedFriction *= 0.9535499811172485;
		if (pressed) {
			player->setSprinting(true);
			if (player->getMovementProxy()->isOnGround()) {
				if (useVelocity && !input->isJumping) player->location->velocity.y = 0.4000000059604645;
				speedFriction = RandomFloat(0.4190652072429657, 0.48381298780441284);
			} else {
				moveVec.x = moveVec2d.x * speedFriction;
				moveVec.y = player->location->velocity.y;
				moveVec.z = moveVec2d.y * speedFriction;
				player->lerpMotion(moveVec);
			}
		}
	} else {
		if (player->getMovementProxy()->isOnGround() && pressed)
			player->jumpFromGround();
		moveVec.x = moveVec2d.x * speed;
		moveVec.y = player->location->velocity.y;
		moveVec.z = moveVec2d.y * speed;
		if (pressed) player->lerpMotion(moveVec);
	}
}