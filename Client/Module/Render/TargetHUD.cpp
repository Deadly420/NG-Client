#include "TargetHUD.h"

TargetHUD::TargetHUD() : Module(0, Category::RENDER, "TargetHUD") {
	registerBoolSetting("Animation", &animation, animation);
}

TargetHUD::~TargetHUD() {
}

const char* TargetHUD::getModuleName() {
	return ("TargetHUD");
}

static std::vector<Entity*> targetList3;

void findPlayers2(Entity* currentEntity, bool isRegularEntity) {
	if (currentEntity == nullptr ||
		currentEntity == Game.getLocalPlayer() ||
		!Game.getLocalPlayer()->canAttack(currentEntity, false) ||
		!Game.getLocalPlayer()->isAlive() ||
		!currentEntity->isAlive() ||
		currentEntity->getEntityTypeId() != 319 ||  // Players
		!Target::isValidTarget(currentEntity) ||
		currentEntity->getEntityTypeId() == 1677999 ||  // Villager
		currentEntity->getEntityTypeId() == 51)         // NPC
	{
		return;
	}

	float dist = (*currentEntity->getPos()).dist(*Game.getLocalPlayer()->getPos());

	if (dist < 10) {
		targetList3.push_back(currentEntity);
	}
}

struct CompareTargetEnArray {
	bool operator()(Entity* lhs, Entity* rhs) {
		LocalPlayer* localPlayer = Game.getLocalPlayer();
		return (*lhs->getPos()).dist(*localPlayer->getPos()) < (*rhs->getPos()).dist(*localPlayer->getPos());
	}
};

void TargetHUD::onTick(GameMode* gm) {
	// Loop through all our players and retrieve their information
	targetList3.clear();

	Game.forEachEntity(findPlayers2);

	for (auto& i : targetList3) {
		if (!(i->damageTime > 1 && hurttime)) {
			targethud++;
		} else
			targethud = 0;
	}
}

void TargetHUD::onPreRender(MinecraftUIRenderContext* renderCtx) {
	std::sort(targetList3.begin(), targetList3.end(), CompareTargetEnArray());
	if (Game.getLocalPlayer() != nullptr && !targetList3.empty()) {	
		// Atributes
		AbsorptionAttribute attribute = AbsorptionAttribute();
		HealthAttribute attribute2 = HealthAttribute();
		float Absorbtion = ((int)targetList3[0]->getAttribute(&attribute)->currentValue);
		float Health = ((int)targetList3[0]->getAttribute(&attribute2)->currentValue);
		float HealthMax = ((int)targetList3[0]->getAttribute(&attribute2)->maximumValue);
		Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
		Vec2 res = Game.getClientInstance()->getGuiData()->windowSize;
		LocalPlayer* player = Game.getClientInstance()->getCILocalPlayer();
		if (player != nullptr) {
			Vec4 rectPos((res.x / 2.f) + (res.x / 20.f), (res.y / 2.f) + (res.y / 24.f), (res.x / 2.f) + (res.x / 6.f), (res.y / 2.f) + (res.y / 8.f));  // Vec4 rectPos((res.x / 2.f) + (res.x / 20.f), (res.y / 2.f) - (res.y / 24.f), (res.x / 2.f) + (res.x / 6.f), (res.y / 2.f) + (res.y / 24.f));
			float rectWidth = rectPos.z - rectPos.x;

			// counter for fade
			counter++;
			if (counter == 100)
				counter--;

			if (animation) {
				positionX += ((rectPos.x - 1) - positionX) * 0.045f;
				positionY += ((rectPos.y - 8) - positionY) * 0.045f;
			} else {
				positionX = rectPos.x - 1;
				positionY = rectPos.y - 8;
			}
			// The actual box
			{
				DrawUtils::fillRectangle(Vec4{positionX + 2.f, positionY + 1.f, rectPos.z + 1, rectPos.w + 1}, Mc_Color(0, 0, 0), counter / 340.33333f);
			}
			// Gets the targets name, then makes it not go to next line
			std::string targetName;
			targetName = Utils::sanitize(targetList3[0]->getNameTag()->getText());
			targetName = targetName.substr(0, targetName.find('\n'));
			std::string HealthString = std::to_string(((int)Health));
			std::string HealthMaxString = std::to_string(((int)HealthMax));
			std::string distance = "Distance: " + std::to_string((int)(*targetList3[0]->getPos()).dist(*Game.getLocalPlayer()->getPos()));
			std::string healthDisplay = "Health: " + HealthString + "/" + HealthMaxString;
			std::string armor = "Armor: ";
			std::string absorptionDisplay;
			// Absorbtion Bar
			if (Absorbtion > 0) {
				std::string absorptionString = std::to_string((int)(Absorbtion));
				absorptionDisplay = " Absorption: " + absorptionString;
				float absorptionBarWidth = (Absorbtion / HealthMax) * rectWidth;
				if (!(targetList3[0]->damageTime > 1))
					DrawUtils::fillRectangle(Vec4(positionX + 3.f, rectPos.y + (res.y / 18.f), rectPos.x + absorptionBarWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), Mc_Color(255, 255, 85), counter / 100.f);
				else
					DrawUtils::fillRectangle(Vec4(positionX + 3.f, rectPos.y + (res.y / 18.f), rectPos.x + absorptionBarWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), Mc_Color(255, 255, 0), counter / 100.f);
			}

			// The text
			{
				// DrawUtils::drawSteve(Vec4(positionX + 2.f, positionY + 1.f, positionX, positionY));
				DrawUtils::drawText(Vec2(positionX + 3.f, rectPos.y - 17 + (res.y / 35.f)), &targetName, Mc_Color(255, 255, 255), 1.f, counter / 100.f);            // name
				DrawUtils::drawText(Vec2(positionX + 3.f, rectPos.y - 8.5 + (res.y / 35.f)), &distance, Mc_Color(255, 255, 255), 0.7f, counter / 100.f);            // distance
				DrawUtils::drawText(Vec2(positionX + 3.f, rectPos.y - 3.5 + (res.y / 35.f)), &healthDisplay, Mc_Color(255, 255, 255), 0.7f, counter / 100.f);       // health
				DrawUtils::drawText(Vec2(positionX + 3.f, rectPos.y - 3.5 + (res.y / 35.f)), &absorptionDisplay, Mc_Color(255, 255, 85), 0.7f, counter / 100.f);    // absorbtion
			}
			DrawUtils::flush();

			// Health Bar
			{
				float healthBarWidth = (Health / HealthMax) * rectWidth;
				if (!(targetList3[0]->damageTime > 1))
					DrawUtils::fillRectangle(Vec4(positionX + 3.f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + healthBarWidth, rectPos.w), Mc_Color(0, 200, 0), counter / 100.f);
				else
					DrawUtils::fillRectangle(Vec4(positionX + 3.f, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2), rectPos.x + healthBarWidth, rectPos.w), Mc_Color(255, 0, 0), counter / 100.f);
			}
			rectPos.y += res.y / 12.f;
			rectPos.w += res.y / 12.f;
		}

		DrawUtils::flush();
	}
}