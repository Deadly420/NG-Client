#include "Bhop.h"

void Bhop::onMove(MoveInputHandler* input) {
	cachedInput = *input;
	yes = input;
	LocalPlayer* player = Game.getLocalPlayer();
	if (player == nullptr)
		return;

	if (player->isInLava() == 1 || player->isInWater() == 1)
		return;

	if (player->isSneaking())
		return;

	Vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
	bool pressed = moveVec2d.magnitude() > 0.01f;

	if (hive) {
		float calcYaw = (player->yaw + 90) * (PI / 180);
		Vec3 moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};

		if (pressed) {
			player->setSprinting(true);
			if (player->onGround) {
				player->jumpFromGround();
			}
			C_MovePlayerPacket mpp(player, *player->getPos());
			mpp.onGround = player->onGround;
			mpp.pitch += 0.5f;
			mpp.yaw += 0.5f;
			mpp.headYaw += 0.5f;
			Game.getClientInstance()->loopbackPacketSender->sendToServer(&mpp);
			if (player->onGround)
				speedIndexThingyForHive = 0;
			float currentSpeed = epicHiveSpeedArrayThingy[speedIndexThingyForHive] * speed;
			moveVec.x = moveVec2d.x * currentSpeed;
			if (player->onGround) {
				moveVec.y = player->velocity.y = height * 0.1f;
			} else {
				moveVec.y = player->velocity.y;
			}
			moveVec.z = moveVec2d.y * currentSpeed;
			player->lerpMotion(moveVec);
			if (speedIndexThingyForHive < 30)
				speedIndexThingyForHive++;
		}
	} else {
		if (player->onGround && pressed)
			player->jumpFromGround();
		float calcYaw = (player->yaw + 90) * (PI / 180);
		Vec3 moveVec;
		float c = cos(calcYaw);
		float s = sin(calcYaw);
		moveVec2d = {moveVec2d.x * c - moveVec2d.y * s, moveVec2d.x * s + moveVec2d.y * c};
		moveVec.x = moveVec2d.x * speed;
		if (player->onGround) {
			moveVec.y = player->velocity.y = height * 0.1f;
		} else {
			moveVec.y = player->velocity.y;
		}
		moveVec.z = moveVec2d.y * speed;
		if (pressed)
			player->lerpMotion(moveVec);
	}
}