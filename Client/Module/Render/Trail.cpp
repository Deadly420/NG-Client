#include "Trail.h"
#include "../../Manager/ModuleManager.h"
#include "../../../Utils/ColorUtil.h"
#include "../../../include/imgui/imgui.h"

Trail::Trail() : Module(0x0, Category::RENDER, "Display movement trails") {

	registerEnumSetting("Mode", &mode, 0, "Changes The Trail Type");
	mode.addEntry("Circles", 0);
	mode.addEntry("Bubbles", 1);

	registerBoolSetting("Rainbow", &Rainbow, Rainbow, "Rainbow");
	registerIntSetting("Duration", &trailDuration, trailDuration, 5, 200, "Duration");
	registerIntSetting("Delay", &trailDelay, trailDelay, 1, 200, "Delay");
}

Trail::~Trail() {
}

const char* Trail::getModuleName() {
	return "Trail";
}

std::string Trail::getModSettings() {
	return mode.GetSelectedEntry().GetName();
}

void Trail::onTick(GameMode* gm) {
	auto localPlayer = Game.getLocalPlayer();
	if (!localPlayer) return;

	countDelay--;
	if (countDelay <= 0) {
		CircleStatus circle;
		auto renderPosition = localPlayer->getRenderPositionComponent()->renderPos;
		circle.pos = Vec3(renderPosition.x, renderPosition.y - localPlayer->getAABBShapeComponent()->aabb.height, renderPosition.z);
		circle.duration = trailDuration;
		Circles.push_back(circle);
		countDelay = trailDelay;
	}

	if (!Circles.empty()) {
		Circles.erase(std::remove_if(Circles.begin(), Circles.end(), [](CircleStatus& currentCircle) {
						  currentCircle.duration--;
						  return currentCircle.duration <= 0;
					  }),
					  Circles.end());
	}
}

void Trail::onPostRender(MinecraftUIRenderContext* renderCtx) {
	auto localPlayer = Game.getLocalPlayer();
	if (!localPlayer) {
		Circles.clear();
		return;
	}
	if (!Game.canUseMoveKeys())
		return;

	int index = 0;

	for (auto& currentCircle : Circles) {
		Vec2 renderPos = DrawUtils::worldToScreen(currentCircle.pos);
		float distance = currentCircle.pos.dist(Game.getClientInstance()->levelRenderer->getOrigin());
		float size = 8 / fmax(1.0f, distance);

		if (renderPos.x > 0 && renderPos.y > 0) {
			if (mode.selected == 0) {
				if (Rainbow)
					DrawUtils::drawCircleFilled(Vec2(renderPos.x, renderPos.y), Vec2(size, size), ColorUtil::getRainbowColor(3, 1, 1, index * 2), 1);
				else
					DrawUtils::drawCircleFilled(Vec2(renderPos.x, renderPos.y), Vec2(size, size), Mc_Color(255, 255, 255), 1);
			} else {
				if (Rainbow)
					DrawUtils::drawCircle(Vec2(renderPos.x, renderPos.y), Vec2(size, size), ColorUtil::getRainbowColor(3, 1, 1, index * 2), 1);
				else
					DrawUtils::drawCircle(Vec2(renderPos.x, renderPos.y), Vec2(size, size), Mc_Color(255, 255, 255), 1);
			}
			++index;
		}
	}
}
