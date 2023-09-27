#include "Killaura.h"

Killaura::Killaura() : Module(0x0, Category::COMBAT, "Attacks entities around you automatically.") {
	// Registering Boolean Settings with Tooltips
	registerBoolSetting("Target Mobs", &targetMobs, targetMobs, "Toggle targeting mobs");
	registerBoolSetting("MultiAura", &isMulti, isMulti, "Toggle multi-aura");
	registerBoolSetting("Rotations", &rotations, rotations, "Toggle rotations");
	registerBoolSetting("Silent Rotations", &silent, silent, "Toggle silent rotations");
	registerBoolSetting("Hurttime", &hurttime, hurttime, "Toggle hurttime");
	registerBoolSetting("AutoWeapon", &autoweapon, autoweapon, "Toggle auto-weapon");

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
		if (isMulti) {
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

void Killaura::onPlayerTick(Player* player) {
	if (!targetList.empty() && rotations) {
		Vec2 angle = Game.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
		// player->getMovementProxy()->setRot(angle);
		player->getActorHeadRotationComponent()->rot.x = angle.y;
		// player->getActorRotationComponent()->rot.y = angle.y; // straf
		player->getMobBodyRotationComponent()->bodyRot = angle.y;
	}
}

void Killaura::onEnable() {
	if (Game.getLocalPlayer() == nullptr)
		setEnabled(false);
}

void Killaura::onSendPacket(Packet* packet) {
	if (packet->isInstanceOf<MovePlayerPacket>() && Game.getLocalPlayer() != nullptr && silent) {
		if (!targetList.empty()) {
		auto* movePacket = reinterpret_cast<MovePlayerPacket*>(packet);
			Vec2 angle = Game.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
			movePacket->pitch = angle.x;
			movePacket->headYaw = angle.y;
			movePacket->yaw = angle.y;
		}
	}
}