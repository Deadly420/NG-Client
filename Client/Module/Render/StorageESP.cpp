#include "StorageESP.h"

#include "../../../Utils/DrawUtils.h"

StorageESP::StorageESP() : Module(0x0, Category::RENDER, "ESP for but storage blocks.") {
	registerEnumSetting("Mode", &mode, 2, "Select the mode for this setting");
	mode.addEntry("2D", 0);
	mode.addEntry("3D", 1);
	mode.addEntry("Outline", 2);
	mode.addEntry("Corners", 3);
	registerFloatSetting("Opacity", &opacity, opacity, 0.1f, 1.f, "Opacity: Adjust the opacity from 0.1 to 1.0");
	registerBoolSetting("Fill", &fill, fill, "Toggle fill mode on/off");
}

StorageESP::~StorageESP() {
}

const char* StorageESP::getModuleName() {
	return "StorageESP";
}

void StorageESP::onPreRender(MinecraftUIRenderContext* renderCtx) {
	if (!Game.isInGame() || !GameData::canUseMoveKeys() || Game.getLocalPlayer() == nullptr || bufferedChestList.empty())
		return;

	auto ourListLock = std::scoped_lock(this->listLock);

	for (const auto& chest : bufferedChestList) {
		Mc_Color flushColor = Mc_Color(1.f, 1.f, 1.f, opacity);

		Vec3 blockPos = chest.lower;
		if (blockPos.x < 0) blockPos.x -= 1;
		if (blockPos.z < 0) blockPos.z -= 1;
		auto storageID = Game.getLocalPlayer()->getRegion()->getBlock(blockPos)->toLegacy()->blockId;

		if (storageID == 54) flushColor = Mc_Color(1.f, 1.f, 1.f, opacity);                     // Normal Chest
		if (storageID == 146) flushColor = Mc_Color(.92f, .14f, .14f, opacity);                 // Trapped Chest
		if (storageID == 130) flushColor = Mc_Color(0.435294f, 0.215686f, 0.631372f, opacity);  // Ender Chest
		if (storageID == 458) flushColor = Mc_Color(0.62f, 0.31f, 0.04f, opacity);              // Barrel
		if (storageID == 205) flushColor = Mc_Color(.49f, .17f, .95f, opacity);                 // Undyed Shulker Box
		if (storageID == 218) flushColor = Mc_Color(.08f, .91f, .99f, opacity);                 // Shulker Box
		DrawUtils::setColor(flushColor.r, flushColor.g, flushColor.b, flushColor.a);
		if (fill && (mode.selected == 0 || mode.selected == 3)) DrawUtils::draw2DBox(chest.lower, chest.upper, (float)fmax(0.5f, 1 / (float)fmax(1, Game.getLocalPlayer()->getPos()->dist(chest.lower))), true);
		switch (mode.selected) {
		case 0:
			DrawUtils::draw2DBox(chest.lower, chest.upper, (float)fmax(0.5f, 1 / (float)fmax(1, Game.getLocalPlayer()->getPos()->dist(chest.lower))));
			break;
		case 2:
			DrawUtils::drawBox(chest.lower, chest.upper, (float)fmax(0.5f, 1 / (float)fmax(1, Game.getLocalPlayer()->getPos()->dist(chest.lower))), fill, 2);
			break;
		case 3:
			DrawUtils::draw2DBox(chest.lower, chest.upper, (float)fmax(0.5f, 1 / (float)fmax(1, Game.getLocalPlayer()->getPos()->dist(chest.lower))), false, true);
			break;
		}
	}
}

void StorageESP::onLevelRender() {
	if (!Game.isInGame() || !GameData::canUseMoveKeys() || Game.getLocalPlayer() == nullptr || bufferedChestList.empty() || mode.selected != 1)
		return;

	auto ourListLock = std::scoped_lock(this->listLock);

	for (const auto& chest : bufferedChestList) {
		Mc_Color flushColor = Mc_Color(1.f, 1.f, 1.f, opacity);

		Vec3 blockPos = chest.lower;
		if (blockPos.x < 0) blockPos.x -= 1;
		if (blockPos.z < 0) blockPos.z -= 1;
		auto storageID = Game.getLocalPlayer()->getRegion()->getBlock(blockPos)->toLegacy()->blockId;

		if (storageID == 54) flushColor = Mc_Color(1.f, 1.f, 1.f, opacity);                     // Normal Chest
		if (storageID == 146) flushColor = Mc_Color(.92f, .14f, .14f, opacity);                 // Trapped Chest
		if (storageID == 130) flushColor = Mc_Color(0.435294f, 0.215686f, 0.631372f, opacity);  // Ender Chest
		if (storageID == 458) flushColor = Mc_Color(0.62f, 0.31f, 0.04f, opacity);              // Barrel
		if (storageID == 205) flushColor = Mc_Color(.49f, .17f, .95f, opacity);                 // Undyed Shulker Box
		if (storageID == 218) flushColor = Mc_Color(.08f, .91f, .99f, opacity);                 // Shulker Box
		
		DrawUtils::setColor(flushColor.r, flushColor.g, flushColor.b, flushColor.a);
		if (!fill) DrawUtils::drawBox3d(chest.lower, chest.upper, 1.f, true); else DrawUtils::drawBox3dFilled(chest.lower, chest.upper, 1.f, true, true);
	}
}

void StorageESP::onTick(GameMode* gm) {
	// Swap list
	auto listLock = Game.lockChestList();
	auto& chestList = Game.getChestList();
	auto ourListLock = std::scoped_lock(this->listLock);

	this->bufferedChestList.clear();
	this->bufferedChestList.insert(this->bufferedChestList.end(), chestList.begin(), chestList.end());
	chestList.clear();
}