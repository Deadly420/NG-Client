#include "EntityJesus.h"

EntityJesus::EntityJesus() : Module(0x0, Category::ENTITY, "Allows entities to walk on water and lava!") {
	registerFloatSetting("Height", &upness, upness, 0.01f, 1.00f, "Height: Control your height from 0.01 to 1.00");
}

EntityJesus::~EntityJesus() {
}

const char* EntityJesus::getModuleName() {
	return "EntityJesus";
}

std::string EntityJesus::getModSettings() {
	return "Solid";
}

static std::vector<Entity*> targetBo;
void findBo(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr)
		return;

	int entityTypeId = currentEntity->getEntityTypeId();
	// PIG: 4876, HORSE:2118423, DONKEY:2118424, MULE:2118425, BOAT:90
	if (entityTypeId != 4876 && entityTypeId != 2118423 && entityTypeId != 2118424 && entityTypeId != 2118425 && entityTypeId != 90)
		return;

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 3) {
		targetBo.push_back(currentEntity);
	}
}

void EntityJesus::onTick(GameMode* gm) {
	targetBo.clear();
	Game.forEachEntity(findBo);

	if (!targetBo.empty()) {
		if (targetBo[0]->isSneaking()) return;
		if (targetBo[0]->isOnFire()) return;

		Vec3 pos = *targetBo[0]->getPos();
		pos.y -= upness;

		pos.z = targetBo[0]->aabb->upper.z;
		pos.x = targetBo[0]->aabb->upper.x;  // upper upper

		Block* block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
		BlockLegacy* blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->location->velocity.y <= 0) {
			Vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->getMovementProxy()->setOnGround(true);
			targetBo[0]->location->velocity.y = 0.f;
		}

		pos.x = targetBo[0]->aabb->lower.x;
		pos.z = targetBo[0]->aabb->lower.z;  // lower lower

		block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->location->velocity.y <= 0) {
			Vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->getMovementProxy()->setOnGround(true);
			targetBo[0]->location->velocity.y = 0.f;
		}

		pos.x = targetBo[0]->aabb->upper.x;  // upper x and lower z

		block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->location->velocity.y <= 0) {
			Vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->getMovementProxy()->setOnGround(true);
			targetBo[0]->location->velocity.y = 0.f;
		}

		pos.x = targetBo[0]->aabb->lower.x;
		pos.z = targetBo[0]->aabb->upper.z;  // lower x and upper z

		block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->location->velocity.y <= 0) {
			Vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->getMovementProxy()->setOnGround(true);
			targetBo[0]->location->velocity.y = 0.f;
		}

		if (targetBo[0]->isInWater()) {
			targetBo[0]->location->velocity.y = 0.1f;
			targetBo[0]->getMovementProxy()->setOnGround(true);

			if (targetBo[0]->isSneaking()) return;
			if (targetBo[0]->isOnFire()) return;

			Vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;

			pos.z = targetBo[0]->aabb->upper.z;
			pos.x = targetBo[0]->aabb->upper.x;  // upper upper

			Block* block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
			BlockLegacy* blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->location->velocity.y <= 0) {
				Vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += upness;
				targetBo[0]->setPos(pos);
				targetBo[0]->getMovementProxy()->setOnGround(true);
				targetBo[0]->location->velocity.y = 0.f;
			}

			pos.x = targetBo[0]->aabb->lower.x;
			pos.z = targetBo[0]->aabb->lower.z;  // lower lower

			block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
			blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->location->velocity.y <= 0) {
				Vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += 0.01f;
				targetBo[0]->setPos(pos);
				targetBo[0]->getMovementProxy()->setOnGround(true);
				targetBo[0]->location->velocity.y = 0.f;
			}

			pos.x = targetBo[0]->aabb->upper.x;  // upper x and lower z

			block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
			blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->location->velocity.y <= 0) {
				Vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += upness;
				targetBo[0]->setPos(pos);
				targetBo[0]->getMovementProxy()->setOnGround(true);
				targetBo[0]->location->velocity.y = 0.f;
			}

			pos.x = targetBo[0]->aabb->lower.x;
			pos.z = targetBo[0]->aabb->upper.z;  // lower x and upper z

			block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
			blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->location->velocity.y <= 0) {
				Vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += upness;
				targetBo[0]->setPos(pos);
				targetBo[0]->getMovementProxy()->setOnGround(true);
				targetBo[0]->location->velocity.y = 0.f;
			}

			if (targetBo[0]->isOnHotBlock() || targetBo[0]->isOnHotBlock()) {
				targetBo[0]->location->velocity.y = 0.1f;
				targetBo[0]->getMovementProxy()->setOnGround(true);
			}
		}
	}
}

void EntityJesus::onLevelRender() {
	targetBo.clear();
	Game.forEachEntity(findBo);

	if (!targetBo.empty()) {
		if (targetBo[0]->isSneaking()) return;
		if (targetBo[0]->isOnFire()) return;

		Vec3 pos = *targetBo[0]->getPos();
		pos.y -= upness;

		pos.z = targetBo[0]->aabb->upper.z;
		pos.x = targetBo[0]->aabb->upper.x;  // upper upper

		Block* block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
		BlockLegacy* blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->location->velocity.y <= 0) {
			Vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->getMovementProxy()->setOnGround(true);
			targetBo[0]->location->velocity.y = 0.f;
		}

		pos.x = targetBo[0]->aabb->lower.x;
		pos.z = targetBo[0]->aabb->lower.z;  // lower lower

		block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->location->velocity.y <= 0) {
			Vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->getMovementProxy()->setOnGround(true);
			targetBo[0]->location->velocity.y = 0.f;
		}

		pos.x = targetBo[0]->aabb->upper.x;  // upper x and lower z

		block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->location->velocity.y <= 0) {
			Vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->getMovementProxy()->setOnGround(true);
			targetBo[0]->location->velocity.y = 0.f;
		}

		pos.x = targetBo[0]->aabb->lower.x;
		pos.z = targetBo[0]->aabb->upper.z;  // lower x and upper z

		block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
		blockLegacy = (block->blockLegacy);

		if (blockLegacy->material->isLiquid && targetBo[0]->location->velocity.y <= 0) {
			Vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;
			pos.y = ceilf(pos.y);
			pos.y += upness;
			targetBo[0]->setPos(pos);
			targetBo[0]->getMovementProxy()->setOnGround(true);
			targetBo[0]->location->velocity.y = 0.f;
		}

		if (targetBo[0]->isInWater()) {
			targetBo[0]->location->velocity.y = 0.1f;
			targetBo[0]->getMovementProxy()->setOnGround(true);

			if (targetBo[0]->isSneaking()) return;
			if (targetBo[0]->isOnFire()) return;

			Vec3 pos = *targetBo[0]->getPos();
			pos.y -= upness;

			pos.z = targetBo[0]->aabb->upper.z;
			pos.x = targetBo[0]->aabb->upper.x;  // upper upper

			Block* block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
			BlockLegacy* blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->location->velocity.y <= 0) {
				Vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += upness;
				targetBo[0]->setPos(pos);
				targetBo[0]->getMovementProxy()->setOnGround(true);
				targetBo[0]->location->velocity.y = 0.f;
			}

			pos.x = targetBo[0]->aabb->lower.x;
			pos.z = targetBo[0]->aabb->lower.z;  // lower lower

			block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
			blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->location->velocity.y <= 0) {
				Vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += 0.01f;
				targetBo[0]->setPos(pos);
				targetBo[0]->getMovementProxy()->setOnGround(true);
				targetBo[0]->location->velocity.y = 0.f;
			}

			pos.x = targetBo[0]->aabb->upper.x;  // upper x and lower z

			block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
			blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->location->velocity.y <= 0) {
				Vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += upness;
				targetBo[0]->setPos(pos);
				targetBo[0]->getMovementProxy()->setOnGround(true);
				targetBo[0]->location->velocity.y = 0.f;
			}

			pos.x = targetBo[0]->aabb->lower.x;
			pos.z = targetBo[0]->aabb->upper.z;  // lower x and upper z

			block = Game.getLocalPlayer()->region->getBlock(Vec3i(pos));
			blockLegacy = (block->blockLegacy);

			if (blockLegacy->material->isSuperHot && targetBo[0]->location->velocity.y <= 0) {
				Vec3 pos = *targetBo[0]->getPos();
				pos.y -= upness;
				pos.y = ceilf(pos.y);
				pos.y += upness;
				targetBo[0]->setPos(pos);
				targetBo[0]->getMovementProxy()->setOnGround(true);
				targetBo[0]->location->velocity.y = 0.f;
			}

			if (targetBo[0]->isOnHotBlock() || targetBo[0]->isOnHotBlock()) {
				targetBo[0]->location->velocity.y = 0.1f;
				targetBo[0]->getMovementProxy()->setOnGround(true);
			}
		}
	}
}