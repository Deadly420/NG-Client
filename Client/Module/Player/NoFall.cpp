#include "NoFall.h"

NoFall::NoFall() : Module(VK_NUMPAD3, Category::PLAYER, "Prevents you from taking falldamage") {
	mode.addEntry(EnumEntry("Vanilla", 0))
		.addEntry(EnumEntry("Mineplex", 1))
		.addEntry(EnumEntry("CubeCraft", 2))
		.addEntry(EnumEntry("Nukkit", 3))
		.addEntry(EnumEntry("AuthGroundPos", 4));
	registerEnumSetting("Mode", &mode, 0, "Mode: Select the desired mode from the available options");
}

NoFall::~NoFall() {}

const char* NoFall::getModuleName() {
	return ("NoFall");
}

void NoFall::onSendPacket(Packet* packet) {
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (localPlayer == nullptr)
		return;

	if (localPlayer->getFallDistanceComponent()->fallDistance > 2.f && mode.selected == 1) {
		if (packet->isInstanceOf<MovePlayerPacket>()) {
			MovePlayerPacket* movePacket = reinterpret_cast<MovePlayerPacket*>(packet);
		}
	}
	if (mode.selected == 4) {
		if (packet->isInstanceOf<PlayerAuthInputPacket>() && !Game.getLocalPlayer()->isOnGround()) {
			PlayerAuthInputPacket* authInput = reinterpret_cast<PlayerAuthInputPacket*>(packet);
			authInput->pos = closestGround;
		}
		/*if (packet->isInstanceOf<MovePlayerPacket>() && !Game.getLocalPlayer()->isOnGround()) { I don't know if this is better to have or not
			MovePlayerPacket* movePacket = reinterpret_cast<MovePlayerPacket*>(packet);
			movePacket->Position = closestGround;
		}*/
	}
}

bool NoFall::isOverVoid() {
	for (float posY = Game.getLocalPlayer()->getPos()->y; posY > 0.0f; --posY) {
		if (!(Game.getLocalPlayer()->getRegion()->getBlock(Vec3(Game.getLocalPlayer()->getPos()->x, posY, Game.getLocalPlayer()->getPos()->z))->blockLegacy->blockId == 0)) {
			return false;
		}
	}
	return true;
};

void NoFall::onTick(GameMode* gm) {
	LocalPlayer* localPlayer = Game.getLocalPlayer();
	if (localPlayer != nullptr) {
		if (localPlayer->getFallDistanceComponent()->fallDistance > 2.f) {
			switch (mode.selected) {
			case 0: {
				PlayerActionPacket actionPacket;
				actionPacket.action = 7;  // Respawn
				actionPacket.entityRuntimeId = localPlayer->getRuntimeIDComponent()->runtimeID;
				Game.getClientInstance()->loopbackPacketSender->sendToServer(&actionPacket);
				break;
			}
			case 2: {
				localPlayer->entityLocation->velocity.y = 0.f;
				localPlayer->setPos((*localPlayer->getPos()).add(0, (float)0.2, 0.f));
				break;
			}
			case 3: {
				PlayerActionPacket actionPacket;
				actionPacket.action = 15;  // Open Elytra
				actionPacket.entityRuntimeId = localPlayer->dimension->dimensionId;
				Game.getClientInstance()->loopbackPacketSender->sendToServer(&actionPacket);
			}
			case 4: {
				Vec3 blockBelow = *localPlayer->getPos();
				blockBelow.y -= localPlayer->aabb->height;
				blockBelow.y -= 0.17999f;
				while (localPlayer->getRegion()->getBlock(blockBelow)->blockLegacy->blockId == 0 && !localPlayer->getRegion()->getBlock(blockBelow)->blockLegacy->isSolid) {
					blockBelow.y -= 1.f;
					if (isOverVoid()) {
						return;
					}
				}
				blockBelow.y += 2.62001f;
				Vec3 pos = *localPlayer->getPos();
				closestGround = {pos.x, blockBelow.y, pos.z};
			}
			}
		}
	}
}