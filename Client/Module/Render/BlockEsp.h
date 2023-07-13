#pragma once
#include "../Module.h"
#include "../../../Utils/HMath.h"
#include "../../../Utils/DrawUtils.h"
#include "../ModuleManager.h"
class BlockEsp : public Module {
public:
	int tickTimeout = 0;
	std::vector<std::shared_ptr<AABB>> bufferedChestList;
	std::mutex listLock;

	float thick = 0.4f;
	bool copper = false;
	bool outline = false;
	bool diamond = false;
	bool emerald = false;
	bool gold = false;
	bool redstone = false;
	bool lapis = false;
	bool iron = false;
	bool coal = false;
	bool debris = false;
	bool quartz = false;
	bool invisBlocks = false;
	bool portalBlocks = false;
	bool spawner = false;

	int range = 10;
	int Odelay = 0;
	float delay = 0.14f;

	BlockEsp() : Module(0x0, Category::RENDER, "Draws a box around specific blocks") {
		registerIntSetting("radius", &range, range, 3, 20);
		registerBoolSetting("Outline shape", &outline, outline);
		registerFloatSetting("Outline Thickness", &thick, thick, 0.1f, 0.8f);

		registerBoolSetting("Emerald ore", &emerald, emerald);
		registerBoolSetting("Diamond ore", &diamond, diamond);
		registerBoolSetting("Gold ore", &gold, gold);
		registerBoolSetting("Redstone ore", &redstone, redstone);
		registerBoolSetting("Lapis ore", &lapis, lapis);
		registerBoolSetting("Iron ore", &iron, iron);
		registerBoolSetting("Coal ore", &coal, coal);
		registerBoolSetting("Copper ore", &copper, copper);
		registerBoolSetting("Ancient Debris", &debris, debris);
		registerBoolSetting("Nether Quartz", &quartz, quartz);
		registerBoolSetting("Invisible Blocks", &invisBlocks, invisBlocks);
		registerBoolSetting("Portal Blocks", &portalBlocks, portalBlocks);
	};
	~BlockEsp(){};
	void onPreRender(MinecraftUIRenderContext* renderCtx) {
		if (!Game.isInGame() || !GameData::canUseMoveKeys() || Game.getLocalPlayer() == nullptr)
			return;

		for (auto iter = bufferedChestList.begin(); iter != bufferedChestList.end(); ++iter) {
			auto storageID = Game.getLocalPlayer()->region->getBlock((*iter)->upper)->blockLegacy->blockId;
			float math = (float)fmax(0.3f, (float)fmin(1.f, 15));
			// RenderUtils::setColor(1.f, 1.f, 1.f, math);

			Vec3 blockPos = (*iter)->lower;
			if (blockPos.x < 0)
				blockPos.x -= 1;

			if (blockPos.z < 0)
				blockPos.z -= 1;

			storageID = Game.getLocalPlayer()->region->getBlock(blockPos)->toLegacy()->blockId;

			auto mathVect = Vec3((*iter)->upper.floor().add(Vec3(1.f, 1.f, 1.f)).sub((*iter)->upper));
			mathVect.y = floor(mathVect.y);

			if (storageID == 54) DrawUtils::setColor(1.f, 1.f, 1.f, math);                       // Normal Chest
			if (storageID == 130) DrawUtils::setColor(0.435294f, 0.215686f, 0.631372f, math);    // Ender Chest
			if (storageID == 205) DrawUtils::setColor(.49f, .17f, .95f, math);                   // Undyed Shulker Box
			if (storageID == 218) DrawUtils::setColor(.08f, .91f, .99f, math);                   // Shulker Box

			if (portalBlocks && storageID == 90) DrawUtils::setColor(.08f, .91f, .99f, math);	// portalBlocks
			if (invisBlocks && storageID == 95) DrawUtils::setColor(.08f, .91f, .99f, math);		// invisBlocks
			if (quartz && storageID == 153) DrawUtils::setColor(.08f, .91f, .99f, math);				// quartz
			if (copper && storageID == 566) DrawUtils::setColor(.08f, .91f, .99f, math);				// copper ore
			if (iron && storageID == 15) DrawUtils::setColor(.08f, .91f, .99f, math);					// iron ore
			if (gold && storageID == 14) DrawUtils::setColor(.08f, .91f, .99f, math);					// gold ore
			if (diamond && storageID == 56) DrawUtils::setColor(.08f, .91f, .99f, math);				// diamond ore
			if (lapis && storageID == 21) DrawUtils::setColor(.08f, .91f, .99f, math);					// lapis ore
			if (redstone && storageID == 73) DrawUtils::setColor(.08f, .91f, .99f, math);				// redstone ore
			if (coal && storageID == 16) DrawUtils::setColor(.08f, .91f, .99f, math);					// coal ore
			if (copper && storageID == 566) DrawUtils::setColor(.08f, .91f, .99f, math);				// copper
			if (emerald && storageID == 129) DrawUtils::setColor(.08f, .91f, .99f, math);				// emerald ore
			if (debris && storageID == 526) DrawUtils::setColor(.08f, .91f, .99f, math);				// ancient debris
			if (spawner && storageID == 52) DrawUtils::setColor(.08f, .91f, .99f, math);				//  mob spawner

			DrawUtils::drawBox((*iter)->lower, (*iter)->upper, (float)fmax(0.2f, 1 / (float)fmax(1, Game.getLocalPlayer()->eyePos0.dist((*iter)->lower))), true);
		}
	}

	virtual const char* getModuleName() override {
		return "BlockEsp";
	}
};