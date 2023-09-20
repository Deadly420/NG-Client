#include "Fly.h"

Fly::Fly() : Module('F', Category::MOVEMENT, "Fly to the sky") {
	//mode.addEntry("Creative", 0);
	//mode.addEntry("CubeGlide", 1);
	//mode.addEntry("AirStuck", 2);
	//mode.addEntry("Jetpack", 3);
	//mode.addEntry("Jetpack2", 4);
	mode.addEntry("Motion", 5);
	registerEnumSetting("Mode", &mode, 5);
	registerFloatSetting("Horizontal Speed", &horizontalSpeed, horizontalSpeed, 0.1f, 10.f, "Horizontal Speed: Adjust horizontal speed from 0.1 to 10.0");
	registerFloatSetting("Vertical Speed", &verticalSpeed, verticalSpeed, 0.1f, 10.f, "Vertical Speed: Adjust vertical speed from 0.1 to 10.0");
}

Fly::~Fly() {
}

const char *Fly::getModuleName() {
	return ("Fly");
}

void Fly::onEnable() {
	switch (mode.selected) {
	case 5:
		if (Game.getLocalPlayer() != nullptr)
			Game.getLocalPlayer()->setPos((*Game.getLocalPlayer()->getPos()).add(Vec3(0, 1, 0)));
		break;
	}
}

void Fly::onTick(GameMode *gm) {
	gameTick++;

	switch (mode.selected) {
	case 0:
		gm->player->setStatusFlag(CAN_FLY, true);
		break;
	case 1: {
		float calcYaw = (gm->player->getActorHeadRotationComponent()->rot.y + 90) * (PI / 180);

		gameTick++;

		Vec3 pos = *Game.getLocalPlayer()->getPos();
		pos.y += 1.3f;
		MovePlayerPacket a(Game.getLocalPlayer(), pos);
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&a);
		pos.y -= 1.3f;
		MovePlayerPacket a2(Game.getLocalPlayer(), pos);
		Game.getClientInstance()->loopbackPacketSender->sendToServer(&a2);

		Vec3 moveVec;
		moveVec.x = cos(calcYaw) * horizontalSpeed;
		moveVec.z = sin(calcYaw) * horizontalSpeed;

		gm->player->lerpMotion(moveVec);

		if (gameTick >= 5) {
			gameTick = 0;
			float yaw = gm->player->getActorHeadRotationComponent()->rot.y * (PI / 180);
			float length = 4.f;

			float x = -sin(yaw) * length;
			float z = cos(yaw) * length;

			gm->player->setPos(pos.add(Vec3(x, 0.5f, z)));
		}
	} break;
	case 2:
		gm->player->entityLocation->velocity = Vec3(0, 0, 0);
		break;

	case 3: {
		float calcYaw = (gm->player->getActorHeadRotationComponent()->rot.y + 90) * (PI / 180);
		float calcPitch = (gm->player->getActorRotationComponent()->rot.x) * -(PI / 180);

		Vec3 moveVec;
		moveVec.x = cos(calcYaw) * cos(calcPitch) * horizontalSpeed;
		moveVec.y = sin(calcPitch) * horizontalSpeed;
		moveVec.z = sin(calcYaw) * cos(calcPitch) * horizontalSpeed;

		gm->player->lerpMotion(moveVec);
	} break;

	case 4: {
		if (gameTick >= 5) {
			float calcYaw = (gm->player->getActorHeadRotationComponent()->rot.y + 90) * (PI / 180);
			float calcPitch = (gm->player->getActorRotationComponent()->rot.x) * -(PI / 180);

			Vec3 pos = *Game.getLocalPlayer()->getPos();
			MovePlayerPacket a(Game.getLocalPlayer(), pos);
			Game.getClientInstance()->loopbackPacketSender->sendToServer(&a);
			pos.y += 0.35f;
			a = MovePlayerPacket(Game.getLocalPlayer(), pos);
			Game.getClientInstance()->loopbackPacketSender->sendToServer(&a);

			gm->player->entityLocation->velocity.y = 0.465f;
			Vec3 moveVec;
			moveVec.x = cos(calcYaw) * cos(calcPitch) * horizontalSpeed;
			moveVec.z = sin(calcYaw) * cos(calcPitch) * horizontalSpeed;

			gm->player->entityLocation->velocity.x = moveVec.x;
			gm->player->entityLocation->velocity.z = moveVec.z;

			float teleportX = cos(calcYaw) * cos(calcPitch) * 0.00000005f;
			float teleportZ = sin(calcYaw) * cos(calcPitch) * 0.00000005f;

			pos = *gm->player->getPos();
			Game.getLocalPlayer()->setPos(Vec3(pos.x + teleportX, pos.y - 0.15f, pos.z + teleportZ));

			gm->player->entityLocation->velocity.y -= 0.15f;
			gameTick = 0;
		}
	}
	case 5:
		gm->player->entityLocation->velocity = Vec3(0, 0, 0);
	}
}

void Fly::onDisable() {
	if (Game.getLocalPlayer() == nullptr)
		return;

	switch (mode.selected) {
	case 0:
		if (Game.getLocalPlayer()->getActorGameTypeComponent()->gameType != GameType::Creative)
			Game.getLocalPlayer()->setStatusFlag(CAN_FLY, false);
		break;
	case 1:
		Game.getLocalPlayer()->entityLocation->velocity = Vec3(0, 0, 0);
	}
}

void Fly::onMove(MoveInputHandler *input) {
	LocalPlayer *localPlayer = Game.getLocalPlayer();
	if (localPlayer == nullptr)
		return;

	switch (mode.selected) {
	case 5: {
		Vec3 *localPlayerPos = localPlayer->getPos();

		float yaw = localPlayer->getActorHeadRotationComponent()->rot.y;
		Vec2 moveVec2d = {input->forwardMovement, -input->sideMovement};
		bool pressed = moveVec2d.magnitude() > 0.01f;

		if (input->isJumping) {
			localPlayer->entityLocation->velocity.y += verticalSpeed;
		}
		if (input->isSneakDown) {
			localPlayer->entityLocation->velocity.y -= verticalSpeed;
		}
		if (input->right) {
			yaw += 90.f;
			if (input->forward)
				yaw -= 45.f;
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
		if (pressed) {
			float calcYaw = (yaw + 90.f) * (PI / 180.f);
			Vec3 moveVec;
			moveVec.x = cos(calcYaw) * horizontalSpeed;
			moveVec.y = localPlayer->entityLocation->velocity.y;
			moveVec.z = sin(calcYaw) * horizontalSpeed;
			localPlayer->lerpMotion(moveVec);
		}
	} break;
	}
}
