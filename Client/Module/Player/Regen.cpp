#include "Regen.h"

#include <regex>

#include "../../../Utils/ColorUtil.h"
#include "../../../Utils/TimerUtil.h"
#include "../../../SDK/Attribute.h"

bool haspickaxe = false;
Vec3i multiBlockPos = Vec3i(0, 0, 0);

using namespace std;
Regen::Regen() : Module(0, Category::COMBAT, "Regenerates your health") {
	registerEnumSetting("Mode", &mode, 0, "Regen Mode");
	mode.addEntry("Normal", 0);
	mode.addEntry("HiveSingle", 1);
	//mode.addEntry("HiveMulti", 2);
	registerFloatSetting("Range", &range, range, 1, 8, "Regen Reach");
	// registerIntSetting("DestroyDelay", &delay, delay, 1, 13);
	registerBoolSetting("Rotation", &rotation, rotation, "Rotations ServerSide");
	registerBoolSetting("Swing", &swing, swing, "Swings when mine");
	registerBoolSetting("Render", &render, render, "Renders Regen Text");
	registerBoolSetting("ShowRotation", &showrotation, showrotation, "Rots ClientSide");
	registerIntSetting("Delay", &delay, delay, 1, 20, "Regen Delay");
}

const char* Regen::getModuleName() {
	return "Regen";
}

bool Regen::selectPickaxe() {
	return true;
}

bool Regen::hasPickaxe() {
	// PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	// Inventory* inv = supplies->inventory;
	// auto prevSlot = supplies->selectedHotbarSlot;

	// for (int n = 0; n < 36; n++) {
	// ItemStack* stack = inv->getItemStack(n);
	// if (stack->item != nullptr) {
	// if (stack->getItem()->isPickaxe()) {
	//	return true;
	// }
	//}
	//}
	return true;
}

bool Regen::includePos(Vec3i pos) {
	for (auto& i : multiRedstone) {
		if (i.blockPos == pos) return true;
	}
	return false;
}

void Regen::onEnable() {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;
	rot = false;
	firstbreak = false;
	continuemine = false;
	canattack = true;
	isregen = true;
	enabledticks = 0;

	openAnim = -500;
	openTimeOffset = 0;
	openTime = 0;

	// delay = 11;

	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	slot = supplies->selectedHotbarSlot;
}

void Regen::onTick(GameMode* gm) {
	auto player = Game.getLocalPlayer();
	auto bhop = moduleMgr->getModule<Speed>();
	auto fly = moduleMgr->getModule<Fly>();
	if (player == nullptr || moduleMgr->getModule<Scaffold>()->isEnabled()) {
		isregen = false;
		return;
	}
	enabledticks++;

	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	static AbsorptionAttribute attribute = AbsorptionAttribute();
	auto timerUtil = new TimerUtil();
	static vector<Vec3i> blocks;
	haspickaxe = true;
	if (Game.canUseMoveKeys()) {
		switch (mode.selected) {
		case 0:  // Vanilla
			// nothing lol
			break;
		case 1:  // FlareonSingle
		{
			// Check Absorpription Health Check
			if (gm->player->getMutableAttribute(&attribute)->currentValue >= 10) {
				isregen = false;
				if (continuemine) gm->stopDestroyBlock(tempblockPos);
				continuemine = false;
				canattack = true;
				enabledticks = 0;
				rot = false;
				destroy = false;
				return;
			} else {
				isregen = true;
			}

			if (enabledticks > delay) {
				isregen = true;
			} else {
				isregen = false;
				canattack = false;
			}

			if (blocks.empty()) {
				for (int x = -range; x <= range; x++) {
					for (int z = -range; z <= range; z++) {
						for (int y = -range; y <= range; y++) {
							if ((*player->getPos()).dist(player->location->pos.add(Vec3(x, y, z))) < range) blocks.push_back(Vec3i(x, y, z));
						}
					}
				}
				// https://www.mathsisfun.com/geometry/pythagoras-3d.html sort = a12 + a22 + ��(x2 + y2 + z2) + an2 ��(a12 + a22 + ��(x2 + y2 + z2) + an2) / 4.f
				sort(blocks.begin(), blocks.end(), [](Vec3i start, Vec3i end) {
					return sqrtf((start.x * start.x) + (start.y * start.y) + (start.z * start.z)) < sqrtf((end.x * end.x) + (end.y * end.y) + (end.z * end.z));
				});
			}

			bool isDestroyed2 = false;

			for (const Vec3i& offset : blocks) {
				blockPos = gm->player->getPos()->add(offset.toVec3t());
				Vec3 blockPos2 = gm->player->getPos()->add(offset.toVec3t());
				destroy = false;

				string name = gm->player->getRegion()->getBlock(blockPos)->toLegacy()->name.getText();
				Vec3i AirCheckPos;
				bool isSafe = false;
				AirCheckPos = blockPos;
				if (name != "lit_redstone_ore" && name != "redstone_ore") continue;
				if (gm->player->getRegion()->getBlock(AirCheckPos.add(0, 1, 0))->blockLegacy->blockId == 0) isSafe = true;
				if (gm->player->getRegion()->getBlock(AirCheckPos.add(0, -1, 0))->blockLegacy->blockId == 0) isSafe = true;
				if (gm->player->getRegion()->getBlock(AirCheckPos.add(1, 0, 0))->blockLegacy->blockId == 0) isSafe = true;
				if (gm->player->getRegion()->getBlock(AirCheckPos.add(-1, 0, 0))->blockLegacy->blockId == 0) isSafe = true;
				if (gm->player->getRegion()->getBlock(AirCheckPos.add(0, 0, 1))->blockLegacy->blockId == 0) isSafe = true;
				if (gm->player->getRegion()->getBlock(AirCheckPos.add(0, 0, -1))->blockLegacy->blockId == 0) isSafe = true;
				if (continuemine) {
					if ((name == "lit_redstone_ore" || name == "redstone_ore") && tempblockPos == blockPos.toVec3t() && isSafe) {
						destroy = true;
						tempblockPos = blockPos.toVec3t();  // moved
					}
				} else {
					if ((name == "lit_redstone_ore" || name == "redstone_ore") && isSafe) {
						destroy = true;
						gm->startDestroyBlock(blockPos, 1, isDestroyed2);
						continuemine = true;
						tempblockPos = blockPos.toVec3t();
					}
				}

				if (destroy /* && tick >= aids*/) {
					slot = supplies->selectedHotbarSlot;
					static bool restored = false;
					if (!selectPickaxe()) {
						if (!restored)
							restored = true;
						else {
							// auto warning = Game.addNotification("Regen", "No Pickaxe Found"); warning->duration = 3;
							// setEnabled(false);
							haspickaxe = false;
							break;
						}
						return;
					}
					restored = false;
					if (isregen) {
						rot = true;
					}
					if (enabledticks > 12) {
						if (isSafe) gm->destroyBlock(&blockPos, 0);
						hasDestroyed = true;
						enabledticks = 0;
						gm->stopDestroyBlock(blockPos);
						continuemine = false;
						rot = false;
					}
					supplies->selectedHotbarSlot = slot;
					return;
				}

				if (hasDestroyed) {
					hasDestroyed = false;
				}
			}

			if (!destroy) {
				isregen = false;
				if (continuemine) gm->stopDestroyBlock(tempblockPos);
				continuemine = false;
				canattack = true;
				enabledticks = 0;
				rot = false;
			} else {
				canattack = true;
			}
		} break;
		}
	}
}

void Regen::onPostRender(MinecraftUIRenderContext* renderCtx) {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;
	static AbsorptionAttribute attribute = AbsorptionAttribute();
	float renderx = Game.getClientInstance()->getGuiData()->windowSize.x / 2;
	float rendery = roundf(Game.getGuiData()->heightGame * 0.75f) + 0.5f;
	Vec2 renderpos = Vec2(renderx, rendery - 30);
	string rendertext = "Regen (" + to_string(int(player->getMutableAttribute(&attribute)->currentValue)) + "/10)";
	if (render) {
		if (haspickaxe) {
			float animTime = min(openTime, 950) / 950.f;
			float textLen = DrawUtils::getTextWidth(&rendertext, animTime) / 2;
			renderpos.x -= textLen;
			if (player->getMutableAttribute(&attribute)->currentValue < 10 && destroy) {
				DrawUtils::drawText(renderpos, &rendertext, ColorUtil::getRainbowColor(2, 1.f, 1, 0), animTime, 1);
			} else {
				openAnim = -500;
				openTimeOffset = 0;
				openTime = 0;
			}
		} else {
			openAnim = -500;
			openTimeOffset = 0;
			openTime = 0;
			string nopickaxe = "No Block Found!";
			float textLen = DrawUtils::getTextWidth(&nopickaxe, 1) / 2;
			renderpos.x -= textLen;
			DrawUtils::drawText(renderpos, &nopickaxe, Mc_Color(255, 0, 0), 1, 1);
		}
	}
}

void Regen::onPlayerTick(Player* player) {
	if (player == nullptr) return;

	if (openTimeOffset == 0)
		openTimeOffset = TimerUtil::getCurrentMs();
	if (openAnim < 150) openAnim += (28 - openAnim) * 0.09f;
	openTime = TimerUtil::getCurrentMs() - openTimeOffset;

	if (isregen && rotation && showrotation) {
		Vec2 regenRot = player->getPos()->CalcAngle(Vec3(blockPos.x, blockPos.y, blockPos.z));

		player->getActorHeadRotationComponent()->rot.y = regenRot.y;
		player->getMobBodyRotationComponent()->bodyRot = regenRot.y;
		player->getMovementProxy()->setYHeadRot(regenRot.y);
	}
}

void Regen::onSendPacket(Packet* packet) {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;
	if (packet->isInstanceOf<PlayerAuthInputPacket>()) {
		auto* movePacket = reinterpret_cast<PlayerAuthInputPacket*>(packet);
		Vec2 regenRot = player->getPos()->CalcAngle(Vec3(blockPos.x, blockPos.y, blockPos.z));
		if (mode.selected == 2) return;
		if (isregen && rotation) {
			movePacket->yaw = regenRot.y;
			movePacket->yawUnused = regenRot.y;
			movePacket->pitch = regenRot.x;

			player->getActorRotationComponent()->rot.x = regenRot.x;
			player->getActorHeadRotationComponent()->rot.x = regenRot.y;
			player->getMobBodyRotationComponent()->bodyRot = regenRot.y;
		}
	}
}

void Regen::onDisable() {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	destroy = false;
	isregen = false;
	rot = false;
	canattack = true;
}
