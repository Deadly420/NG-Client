#pragma once
#include "../Module.h"
#include "../../../Utils/HMath.h"
#include "../../../Utils/DrawUtils.h"
#include "../ModuleManager.h"
class HoleESP : public Module {
public:
	bool obsidian = true;
	bool bedrock = true;
	int range = 5;
	SettingEnum mode = this;

	HoleESP() : Module(0x0, Category::RENDER, "Highlight Holes") {
		registerEnumSetting("Mode", &mode, 3);
		mode.addEntry("FullBox", 0);
		mode.addEntry("Outline", 1);
		mode.addEntry("Lines", 2);

		registerIntSetting("Range", &range, range, 1, 15);
		registerBoolSetting("Obsidian Hole", &obsidian, obsidian);
		registerBoolSetting("Bedrock Hole", &bedrock, bedrock);
	};
	~HoleESP(){};

	void onPostRender(MinecraftUIRenderContext* renderCtx) {
		if (!(Game.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
			if (Game.isInGame()) {
				Vec3* pos = Game.getLocalPlayer()->getPos();
				for (int x = (int)pos->x - range; x < pos->x + range; x++) {
					for (int z = (int)pos->z - range; z < pos->z + range; z++) {
						for (int y = (int)pos->y - range; y < pos->y + range; y++) {
							Vec3 blockPos = Vec3(x, y, z);
							Vec3 blockPos2 = Vec3(x + 1, y, z);
							Vec3 blockPos3 = Vec3(x, y, z + 1);
							Vec3 blockPos4 = Vec3(x, y - 1, z);
							Vec3 blockPos5 = Vec3(x - 1, y, z);
							Vec3 blockPos6 = Vec3(x, y, z - 1);

							Block* block = Game.getLocalPlayer()->region->getBlock(blockPos);
							Block* block2 = Game.getLocalPlayer()->region->getBlock(blockPos2);
							Block* block3 = Game.getLocalPlayer()->region->getBlock(blockPos3);
							Block* block4 = Game.getLocalPlayer()->region->getBlock(blockPos4);
							Block* block5 = Game.getLocalPlayer()->region->getBlock(blockPos5);
							Block* block6 = Game.getLocalPlayer()->region->getBlock(blockPos6);

							if (block != nullptr && block2 != nullptr && block3 != nullptr && block4 != nullptr) {
								int blockId = block->toLegacy()->blockId;
								int blockId2 = block2->toLegacy()->blockId;
								int blockId3 = block3->toLegacy()->blockId;
								int blockId4 = block4->toLegacy()->blockId;
								int blockId5 = block5->toLegacy()->blockId;
								int blockId6 = block6->toLegacy()->blockId;

								bool obs = false;

								if (blockId == 0) obs = true;

								// Draw Obsidian Hole
								if (obsidian) {
									auto vec1 = Vec3(1.f, 0.1f, 1.f);
									if ((blockId2 == 49 && blockId3 == 49 && blockId4 == 49 && blockId5 == 49 && blockId6 == 49 && blockId == 0)) {
										if (Game.getLocalPlayer()->region->getBlock(blockPos.add(0, 1, 0))->blockLegacy->blockId != 0)
											continue;

										if (Game.getLocalPlayer()->region->getBlock(blockPos.add(0, 2, 0))->blockLegacy->blockId)
											continue;
										if (mode.selected == 2) {
											DrawUtils::drawBoxv2(blockPos, Vec3(blockPos).add(1), (float)0.4f);
											DrawUtils::setColor(0, 255, 0, 1);
										}
										if (mode.selected == 1) {
											DrawUtils::drawBox(blockPos, blockPos.add(vec1), 0.5f, true);
											DrawUtils::setColor(0, 255, 0, 1);
										}
										if (mode.selected == 0) {
											DrawUtils::drawBox(blockPos, Vec3(blockPos).add(1), (float)0.4f);
											DrawUtils::setColor(0, 255, 0, 1);
										}
									}
								}

								// Draw Bedrock Hole
								if (bedrock) {
									auto vec1 = Vec3(1.f, 0.1f, 1.f);
									if ((blockId2 == 7 && blockId3 == 7 && blockId4 == 7 && blockId5 == 7 && blockId6 == 7 && blockId == 0)) {
										if (Game.getLocalPlayer()->region->getBlock(blockPos.add(0, 1, 0))->blockLegacy->blockId != 0)
											continue;

										if (Game.getLocalPlayer()->region->getBlock(blockPos.add(0, 2, 0))->blockLegacy->blockId)
											continue;
										if (mode.selected == 2) {
											DrawUtils::drawBoxv2(blockPos, Vec3(blockPos).add(1), (float)0.4f);
											DrawUtils::setColor(0, 255, 0, 1);
										}
										if (mode.selected == 1) {
											DrawUtils::drawBox(blockPos, blockPos.add(vec1), 0.5f, true);
											DrawUtils::setColor(0, 255, 0, 1);
										}
										if (mode.selected == 0) {
											DrawUtils::drawBox(blockPos, Vec3(blockPos).add(1), (float)0.4f);
											DrawUtils::setColor(0, 255, 0, 1);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	virtual const char* getModuleName() override {
		return "HoleESP";
	}
};