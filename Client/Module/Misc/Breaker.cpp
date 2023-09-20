#include "Breaker.h"

Breaker::Breaker() : Module(0x0, Category::MISC, "Destroys certain blocks around you.") {
	registerIntSetting("Range", &range, range, 1, 10, "Range: Set the range from 1 to 10");
	registerBoolSetting("Beds", &beds, beds, "Beds: Toggle beds");
	registerBoolSetting("Eggs", &eggs, eggs, "Eggs: Toggle eggs");
	registerBoolSetting("Cakes", &cakes, cakes, "Cakes: Toggle cakes");
	registerBoolSetting("Treasures", &treasures, treasures, "Treasures: Toggle treasures");
	registerBoolSetting("Chests", &chests, chests, "Chests: Toggle chests");
	registerBoolSetting("Barrels", &barrels, barrels, "Barrels: Toggle barrels");
}

Breaker::~Breaker() {
}

const char* Breaker::getModuleName() {
	return ("Breaker");
}

void Breaker::onTick(GameMode* gm) {
	Vec3* pos = gm->player->getPos();
	for (int x = (int)pos->x - range; x < pos->x + range; x++) {
		for (int z = (int)pos->z - range; z < pos->z + range; z++) {
			for (int y = (int)pos->y - range; y < pos->y + range; y++) {
				Vec3i blockPos = Vec3i(x, y, z);
				bool destroy = false;
				bool eat = false;
				auto id = gm->player->getRegion()->getBlock(blockPos)->toLegacy()->blockId;

				if (id == 26 && beds) destroy = true;      // Beds
				if (id == 122 && eggs) destroy = true;     // Dragon Eggs
				if (id == 92 && cakes) eat = true;         // Cakes
				if (id == 54 && chests) destroy = true;    // Chests
				if (id == 458 && barrels) destroy = true;  // Barrels

				if (destroy) {
					gm->destroyBlock(&blockPos, 0);
					Game.getLocalPlayer()->swingArm();
					return;
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

	if (treasures) {
		Game.forEachEntity([](Entity* ent, bool b) {
			std::string name = ent->getNameTag()->getText();
			int id = ent->getEntityTypeId();
			if (name.find("Treasure") != std::string::npos && Game.getLocalPlayer()->getPos()->dist(*ent->getPos()) <= 5) {
				Game.getLocalPlayer()->swingArm();
				Game.getGameMode()->attack(ent);
			}
		});
	}
}
