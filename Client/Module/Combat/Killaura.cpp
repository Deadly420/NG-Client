#include "Killaura.h"

Killaura::Killaura() : Module(0x0, Category::COMBAT, "Attacks entities around you automatically.") {
	registerEnumSetting("Mode", &mode, 0, "");
	mode.addEntry("Single", 0);
	mode.addEntry("Multi", 1);

	registerEnumSetting("Rotations", &rotationMode, 2, "");
	rotationMode.addEntry("None", 0);
	rotationMode.addEntry("Silent", 1);
	rotationMode.addEntry("Strafe", 2);
	rotationMode.addEntry("Normal", 3);

	// Registering Boolean Settings with Tooltips
	registerBoolSetting("Target Mobs", &targetMobs, targetMobs, "Toggle targeting mobs");
	registerBoolSetting("Hurttime", &hurttime, hurttime, "Toggle hurttime");
	// registerBoolSetting("AutoWeapon", &autoweapon, autoweapon, "Toggle auto-weapon");

	// Registering Float Settings with Tooltips
	registerFloatSetting("Range", &range, range, 2.f, 7.f, "Range: Adjust the range from 2.0 to 7.0");

	// Registering Integer Settings
	registerIntSetting("MinDelay", &minD, minD, 0, 20, "MinDelay: Adjust the minimum delay from 0 to 20");
	registerIntSetting("MaxDelay", &maxD, maxD, 0, 20, "MaxDelay: Adjust the maximum delay from 0 to 20");
}

Killaura::~Killaura() {
}

const char* Killaura::getModuleName() {
	return "Killaura";
}

static std::vector<Entity*> targetList;
void findEntity(Entity* currentEntity, bool isRegularEntity) {
	static auto killauraMod = moduleMgr->getModule<Killaura>();

	if (currentEntity == nullptr)
		return;

	if (currentEntity == Game.getLocalPlayer())  // Skip Local player
		return;

	if (!Game.getLocalPlayer()->canAttack(currentEntity, false))
		return;

	if (!Game.getLocalPlayer()->isAlive())
		return;

	if (!currentEntity->isAlive())
		return;

	if (currentEntity->getEntityTypeId() == 66)  // falling block
		return;

	if (currentEntity->getEntityTypeId() == 69)  // XP
		return;

	if (killauraMod->targetMobs) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63)
			return;
		if (currentEntity->getAABBShapeComponent()->aabb.width <= 0.01f || currentEntity->getAABBShapeComponent()->aabb.height <= 0.01f)  // Don't hit this pesky antibot on 2b2e.org
			return;
		if (currentEntity->getEntityTypeId() == 64)  // item
			return;
		if (currentEntity->getEntityTypeId() == 80)  // Arrows
			return;
		if (currentEntity->getEntityTypeId() == 51)  // NPC
			return;
	} else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < killauraMod->range) {
		targetList.push_back(currentEntity);
	}
}

void Killaura::findWeapon() {
	PlayerInventoryProxy* supplies = Game.getLocalPlayer()->getSupplies();
	Inventory* inv = supplies->inventory;
	float damage = 0;
	int slot = supplies->selectedHotbarSlot;
	for (int n = 0; n < 9; n++) {
		ItemStack* stack = inv->getItemStack(n);
		if (stack->item != nullptr) {
			float currentDamage = stack->getAttackingDamageWithEnchants();
			if (currentDamage > damage) {
				damage = currentDamage;
				slot = n;
			}
		}
	}
	supplies->selectedHotbarSlot = slot;
}

void Killaura::onTick(GameMode* gm) {
	targetListEmpty = targetList.empty();
	// Loop through all our players and retrieve their information
	targetList.clear();
	if (Game.canUseMoveKeys() || Game.isInGame()) {
		Game.forEachEntity(findEntity);

		delay++;
		if (minD <= maxD) {
			if (!targetList.empty() && delay >= random(minD, maxD)) {
				if (autoweapon) findWeapon();

				if (Game.getLocalPlayer()->location->velocity.squaredxzlen() < 0.01) {
					MovePlayerPacket p(Game.getLocalPlayer(), *Game.getLocalPlayer()->getPos());
					Game.getClientInstance()->loopbackPacketSender->sendToServer(&p);  // make sure to update rotation if player is standing still
				}

				// Attack all entitys in targetList
				if (mode.selected == 1) {
					for (auto& i : targetList) {
						if (!(i->damageTime > 1 && hurttime)) {
							Game.getLocalPlayer()->swing();
							Game.getGameMode()->attack(i);
						}
					}
				} else {
					if (!(targetList[0]->damageTime > 1 && hurttime)) {
						Game.getLocalPlayer()->swing();
						Game.getGameMode()->attack(targetList[0]);
					}
				}
				delay = 0;
			}
		}
	}
}

void Killaura::onPlayerTick(Player* player) {
	if (Game.getLocalPlayer() != nullptr && !targetList.empty() && rotationMode.selected > 1) {
		if (targetList[0] == nullptr)
			return;

		Vec2 angle = Game.getLocalPlayer()->getPos()->CalcAngle(targetList[0]->getMovementProxy()->getAttachPos(ActorLocation::Eyes, 1.f));

		if (rotationMode.selected == 3)
			player->getActorRotationComponent()->rot.x = angle.x;
		else if (rotationMode.selected == 2)
			player->getActorRotationComponent()->rot = angle;

		player->getActorHeadRotationComponent()->rot.y = angle.y;
		player->getMobBodyRotationComponent()->bodyRot = angle.y;
		player->getMovementProxy()->setYHeadRot(angle.y);
	}
}

void Killaura::onEnable() {
	if (Game.getLocalPlayer() == nullptr)
		setEnabled(false);
}

void Killaura::onSendPacket(Packet* packet) {
	if (Game.getLocalPlayer() != nullptr && rotationMode.selected >= 1 && !targetList.empty() && Game.isInGame()) {
		if (targetList[0] == nullptr)
			return;

		if (packet->isInstanceOf<MovePlayerPacket>()) {
			auto* movePacket = reinterpret_cast<MovePlayerPacket*>(packet);
			Vec2 angle = Game.getLocalPlayer()->getPos()->CalcAngle(targetList[0]->getMovementProxy()->getAttachPos(ActorLocation::Eyes, 1.f));
			movePacket->pitch = angle.y;
			movePacket->headYaw = angle.y;
			movePacket->yaw = angle.y;
		}
	}
}

void Killaura::onLevelRender() {
	auto player = Game.getLocalPlayer();
	if (player == nullptr) return;

	static float n = 0;
	static float anim = 0;
	if (Game.canUseMoveKeys() && !targetList.empty()) {
		anim++;
		DrawUtils::setColor(1, 0, 0, 1);

		Vec3 permutations[56];
		for (int i = 0; i < 56; i++) {
			permutations[i] = {sinf((i * 10.f) / (180 / PI)), 0.f, cosf((i * 10.f) / (180 / PI))};
		}

		const float animation = 0.9f + 0.9f * sin((anim / 20) * PI * 1);

		Vec3* start = targetList[0]->getPosOld();
		Vec3* end = targetList[0]->getPos();

		auto te = DrawUtils::getLerpTime();
		Vec3 pos = start->lerp(end, te);

		auto yPos = pos.y;
		yPos = 2.0f;  // Increase this value to raise the rendering above the player
		yPos += animation;

		std::vector<Vec3> posList;
		posList.reserve(54);
		for (auto& perm : permutations) {
			Vec3 curPos(pos.x, yPos, pos.z);
			posList.push_back(curPos.add(perm));
		}
		DrawUtils::drawLinestrip3d(posList);
	}
}