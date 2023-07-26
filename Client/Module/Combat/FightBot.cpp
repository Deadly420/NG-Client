#include "FightBot.h"

FightBot::FightBot() : Module(0x0, Category::COMBAT, "Attacks entities around you automatically") {
	registerIntSetting("TargetRange", &targ, targ, 50, 500);
	registerFloatSetting("HitRange", &range, range, 2.f, 20.f);
	registerIntSetting("delay", &delay, delay, 0, 20);
	registerBoolSetting("MultiAura", &isMulti, isMulti);
	registerBoolSetting("MobAura", &isMobAura, isMobAura);
	registerBoolSetting("hurttime", &hurttime, hurttime);
	registerBoolSetting("AutoWeapon", &autoweapon, autoweapon);
	registerBoolSetting("Silent Rotations", &silent, silent);
	registerBoolSetting("NoSwing", &noSwing, noSwing);
}

FightBot::~FightBot() {
}

const char* FightBot::getModuleName() {
	return "FightBot";
}

struct CompareTargetEnArray {
	bool operator()(Entity* lhs, Entity* rhs) {
		LocalPlayer* localPlayer = Game.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

static std::vector<Entity*> targetList;
void findadEntity(Entity* currentEntity, bool isRegularEntity) {
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	static auto FightBotMod = moduleMgr->getModule<FightBot>();

	if (currentEntity == nullptr || currentEntity == Game.getLocalPlayer() || !Game.getLocalPlayer()->canAttack(currentEntity, false) || !Game.getLocalPlayer()->isAlive() || !currentEntity->isAlive() || currentEntity->width <= 0.1f || currentEntity->height <= 0.1f)
		return;

	if (FightBotMod->isMobAura) {
		if (currentEntity->getNameTag()->getTextLength() <= 1 && currentEntity->getEntityTypeId() == 63 || currentEntity->width <= 0.01f || currentEntity->height <= 0.01f || currentEntity->getEntityTypeId() == 64 || currentEntity->getEntityTypeId() == 69)
			return;
	} else {
		if (!Target::isValidTarget(currentEntity))
			return;
	}

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());
	if (dist < FightBotMod->targ) {
		targetList.push_back(currentEntity);
	}
}

void FightBot::findWeapon() {
	if (Game.isInGame()) {
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
}

void FightBot::onTick(GameMode* gm) {
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	targetListA = targetList.empty();

	if (!Game.isInGame()) {
		return;
	}

	Game.forEachEntity(findadEntity);
	Game.getClientInstance()->getMoveTurnInput()->forward = true;
	Game.getClientInstance()->getCILocalPlayer()->setSprinting(true);

	if (autoweapon) {
		findWeapon();
	}

	if (!targetList.empty()) {
		Odelay++;

		if (Odelay >= delay) {
			if (isMulti) {
				for (auto& i : targetList) {
					float dist = (*i->getPos()).dist(*Game.getLocalPlayer()->getPos());
					if (!(i->damageTime > 1 && hurttime) && dist < range) {
						if (!noSwing) {
							Game.getLocalPlayer()->swing();
						}
						Game.getGameMode()->attack(i);
					}
				}
			} else {
				float dist = (*targetList[0]->getPos()).dist(*Game.getLocalPlayer()->getPos());
				if (!(targetList[0]->damageTime > 1 && hurttime) && dist < range) {
					if (!noSwing) {
						Game.getLocalPlayer()->swing();
					}
					Game.getGameMode()->attack(targetList[0]);
				}
			}

			Odelay = 0;
		}
	}
}

void FightBot::onLevelRender() {
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	targetListA = targetList.empty();
	if (Game.isInGame()) {
		targetList.clear();
		Game.forEachEntity(findadEntity);

		if (!targetList.empty()) {
			if (sexy) {
				joe = Game.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos()).normAngles();
				LocalPlayer* player = Game.getLocalPlayer();
				Vec2 angle = Game.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos()).normAngles();
				player->bodyYaw = angle.x;
				player->bodyYaw = angle.y;
			}
			int prevSlot;
			if (autoweapon) {
				auto supplies = Game.getLocalPlayer()->getSupplies();
				prevSlot = supplies->selectedHotbarSlot;
				auto FinishSelect = true;
				auto inv = supplies->inventory;
				for (int n = 0; n < 9; n++) {
					ItemStack* stack = inv->getItemStack(n);
					if (stack->item != nullptr) {
						if (stack->getItem()->isWeapon()) {
							if (prevSlot != n)
								supplies->selectedHotbarSlot = n;
							return;
						}
					}
				}
			}
		}
	}
	if (!Game.isInGame())
		setEnabled(false);
}

void FightBot::onEnable() {
	std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
	targetList.clear();
	if (Game.isInGame()) {
		if (Game.getLocalPlayer() == nullptr)
			setEnabled(false);
	}
}
void FightBot::onDisable() {
	targetList.clear();
	Game.getClientInstance()->getMoveTurnInput()->forward = false;
	Game.getClientInstance()->getCILocalPlayer()->setSprinting(false);
	Game.getClientInstance()->getMoveTurnInput()->clearMovementState();
}

void FightBot::onSendPacket(Packet* packet) {
	if (Game.isInGame()) {
		if (!Game.isInGame()) {
			auto hop = moduleMgr->getModule<Bhop>();
			hop->setEnabled(false);
		}
		targetListA = targetList.empty();
		targetList.clear();
		Game.forEachEntity(findadEntity);
		std::sort(targetList.begin(), targetList.end(), CompareTargetEnArray());
		if (packet->isInstanceOf<C_MovePlayerPacket>() && Game.getLocalPlayer() != nullptr && silent) {
			if (!targetList.empty()) {
				auto* movePacket = reinterpret_cast<C_MovePlayerPacket*>(packet);
				Vec2 angle = Game.getLocalPlayer()->getPos()->CalcAngle(*targetList[0]->getPos());
				movePacket->pitch = angle.x;
				movePacket->headYaw = angle.y;
				movePacket->yaw = angle.y;
			}
		}
	}
}