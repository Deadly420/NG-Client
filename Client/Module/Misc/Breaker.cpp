#include "../../../SDK/Attribute.h"
#include "Breaker.h"

Breaker::Breaker() : Module(0x0, Category::WORLD, "Destroys specific things around you") {
	registerBoolSetting("Rotations", &rots, rots, "Rotations: Enable or disable rotations");
	registerBoolSetting("Hive Bypass", &bypass, bypass, "Hive Bypass: Enable or disable bypassing on Hive");
	registerBoolSetting("No Swing", &noSwing, noSwing, "No Swing: Enable or disable swinging animation");
	registerFloatSetting("Range", &range, range, 1.0f, 7.0f, "Range: Adjust the range from 1.0 to 7.0");
	registerIntSetting("Delay", &delay, delay, 0, 30, "Delay: Set the delay between actions (0-30)");
	registerIntSetting("Mine Delay", &mineDelay, mineDelay, 0, 30, "Mine Delay: Set the delay between mining actions (0-30)");
	registerBoolSetting("Beds", &beds, beds, "Beds: Enable or disable targeting beds");
	registerBoolSetting("Eggs", &eggs, eggs, "Eggs: Enable or disable targeting eggs");
	registerBoolSetting("Cakes", &cakes, cakes, "Cakes: Enable or disable targeting cakes");
	registerBoolSetting("Treasures", &treasures, treasures, "Treasures: Enable or disable targeting treasures");
	registerBoolSetting("Ender Chests", &echests, echests, "Ender Chests: Enable or disable targeting ender chests");
	registerBoolSetting("Chests", &chests, chests, "Chests: Enable or disable targeting regular chests");
	registerBoolSetting("Redstone Ore", &redstone, redstone, "Redstone Ore: Enable or disable targeting redstone ore");
	registerBoolSetting("Diamonds", &diamond, diamond, "Diamonds: Enable or disable targeting diamond ore");
	registerBoolSetting("Emeralds", &emerald, emerald, "Emeralds: Enable or disable targeting emerald ore");
	registerBoolSetting("Gold Ore", &gOre, gOre, "Gold Ore: Enable or disable targeting gold ore");
	registerBoolSetting("Lapis Ore", &lOre, lOre, "Lapis Ore: Enable or disable targeting lapis lazuli ore");
	registerBoolSetting("Iron Ore", &iron, iron, "Iron Ore: Enable or disable targeting iron ore");
}

Breaker::~Breaker() {
}

const char* Breaker::getModuleName() {
	return "Breaker";
}

void Breaker::onTick(GameMode* gm) {
	delayTimer++;
	if (delayTimer >= delay) {
		delayTimer = 0;
		if (Game.isInGame() && Game.canUseMoveKeys() && Game.getClientInstance()->getCILocalPlayer()->isAlive()) {
			Vec3* pos = gm->player->getPos();
			for (int x = (int)pos->x - range; x < pos->x + range; x++) {
				for (int z = (int)pos->z - range; z < pos->z + range; z++) {
					for (int y = (int)pos->y - range; y < pos->y + range; y++) {
						blockPos = Vec3i(x, y, z);
						destroy = false;
						bool eat = false;
						auto id = gm->player->getRegion()->getBlock(blockPos)->toLegacy()->blockId;
						std::string name = gm->player->getRegion()->getBlock(blockPos)->toLegacy()->name.getText();

						static AbsorptionAttribute attribute = AbsorptionAttribute();

						if (name == "bed" && beds) destroy = true;  // Beds
						if (name == "dragon_egg" && eggs) destroy = true;  // Dragon Eggs
						if (name == "cake" && cakes) eat = true;  // Cakes
						if (name == "chest" && chests) destroy = true;  // Chests
						if (name == "ender_chest" && chests) destroy = true;  // EnderChests
						if (name == "lit_redstone_ore" && redstone && gm->player->getAttribute(&attribute)->currentValue < 10) destroy = true;  // Lit Redstone
						if (name == "redstone_ore" && redstone && gm->player->getAttribute(&attribute)->currentValue < 10) destroy = true;  // Redstone
						if (name == "diamond_ore" && diamond) destroy = true;  // Diamond
						if (name == "emerald_ore" && emerald) destroy = true;  // Emerald
						if (name == "gold_ore" && gOre) destroy = true;  // Gold
						if (name == "lapis_ore" && lOre) destroy = true;  // lapis
						if (name == "iron_ore" && iron) destroy = true;  // Iron
						if (name == "iron_ore" && iron) destroy = true;  // Iron

						if (destroy) {
							if (!bypass)
								gm->destroyBlock(&blockPos, 0);
							else {
								bool isDestroyed = false;
								gm->startDestroyBlock(blockPos, 0, isDestroyed);
								mineDelayTimer++;
								if (mineDelayTimer >= mineDelay) {
									mineDelayTimer = 0;
									gm->stopDestroyBlock(blockPos);
									gm->destroyBlock(&blockPos, 0);
									return;
								}
							}
						}
						if (eat) {
							bool idk = true;
							gm->buildBlock(&blockPos, 0, idk);
							Game.getLocalPlayer()->swingArm();
							return;
						}
					}
				}
			}
		}
	}
}

void Breaker::onPlayerTick(Player* player) {
	if (Game.isInGame() && Game.canUseMoveKeys() && Game.getClientInstance()->getCILocalPlayer()->isAlive()) {
		if (destroy && rots) {
			Vec2 angle = Game.getLocalPlayer()->getPos()->CalcAngle(Vec3(blockPos.x, blockPos.y, blockPos.z));
			player->getMovementProxy()->setRot(angle);
		}
	}
}

void Breaker::onSendPacket(Packet* packet) {
	if (packet->isInstanceOf<MovePlayerPacket>() || packet->isInstanceOf<PlayerAuthInputPacket>() && Game.getLocalPlayer() != nullptr && bypass) {
		if (destroy && Game.isInGame() && packet != nullptr) {
			auto* movePacket = reinterpret_cast<MovePlayerPacket*>(packet);
			Vec2 angle = Game.getLocalPlayer()->getPos()->CalcAngle(Vec3(blockPos.x, blockPos.y, blockPos.z));
			movePacket->pitch = angle.x;
			movePacket->yaw = angle.y;
			movePacket->headYaw = angle.y;
		}
	}
}

void Breaker::onLevelRender() {
	if (treasures) {
		if (Game.isInGame() && Game.canUseMoveKeys() && Game.getClientInstance()->getCILocalPlayer()->isAlive()) {
			Game.forEachEntity([](Entity* ent, bool b) {
				std::string targetName = ent->getNameTag()->getText();
				std::string localName = Game.getLocalPlayer()->getNameTag()->getText();
				auto TeamsMod = moduleMgr->getModule<Teams>();
				if (targetName.find("Treasure") != std::string::npos && Game.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= 5 && targetName.length() > 2 && localName.length() > 2 && targetName.at(2) != localName.at(2)) {
					Game.getGameMode()->attack(ent);
					auto breakMod = moduleMgr->getModule<Breaker>();
					if (!breakMod->noSwing)
						Game.getLocalPlayer()->swingArm();
				}
			});
		}
	}
}