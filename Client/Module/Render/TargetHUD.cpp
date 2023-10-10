#include "TargetHUD.h"

TargetHUD::TargetHUD() : Module(0, Category::RENDER, "TargetHUD") {
}

TargetHUD::~TargetHUD() {}

const char* TargetHUD::getModuleName() {
	return "TargetHUD";
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
}

void TargetHUD::onImGuiRender() {
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowRounding = 10.f;
	style->GrabRounding = 3.0f;
	style->FrameRounding = 6.f;

	if (Game.isInGame() && Game.getLocalPlayer() != nullptr && !targetList3.empty()) {
		ImGui::SetWindowSize(ImVec2(245, 135));
		ImGui::SetWindowPos(ImVec2(100, 100));
		if (ImGui::Begin("TargetHUD", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar)) {
			// Sort the target list
			std::sort(targetList3.begin(), targetList3.end(), CompareTargetEnArray());

			// Attributes
			AbsorptionAttribute attribute = AbsorptionAttribute();
			HealthAttribute attribute2 = HealthAttribute();

			// Extract attribute values
			float Absorption = static_cast<int>(targetList3[0]->getAttribute(&attribute)->currentValue);
			float Health = static_cast<int>(targetList3[0]->getAttribute(&attribute2)->currentValue);
			float HealthMax = static_cast<int>(targetList3[0]->getAttribute(&attribute2)->maximumValue);
			float distance = static_cast<float>(targetList3[0]->getPos()->dist(*Game.getLocalPlayer()->getPos()));
			std::string targetName = Utils::sanitize(targetList3[0]->getNameTag()->getText());
			targetName = targetName.substr(0, targetName.find('\n'));

			// Render the "Name" line unconditionally
			ImGui::Text("Name: %s", targetName.c_str());
			ImGui::Text("Distance: %.1f", static_cast<float>(distance));
			ImGui::Text("Health: %d / %d", static_cast<int>(Health), static_cast<int>(HealthMax));
			ImGui::Text("Absorption: %d", static_cast<int>(Absorption));

			float healthBarWidth = (Health / HealthMax) * 200;

			// Draw the health bar
			ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));  // Green
			ImGui::ProgressBar(Health / HealthMax, ImVec2(healthBarWidth, 10), "");
			ImGui::PopStyleColor();

			ImGui::End();
		}
	}
}

/*void TargetHUD::onPreRender(MinecraftUIRenderContext* renderCtx) {
	// Sort the target list
	std::sort(targetList3.begin(), targetList3.end(), CompareTargetEnArray());

	// Check if the local player is not null and the target list is not empty
	if (Game.getLocalPlayer() != nullptr && !targetList3.empty()) {
		// Attributes
		AbsorptionAttribute attribute = AbsorptionAttribute();
		HealthAttribute attribute2 = HealthAttribute();

		// Extract attribute values
		float Absorption = static_cast<int>(targetList3[0]->getAttribute(&attribute)->currentValue);
		float Health = static_cast<int>(targetList3[0]->getAttribute(&attribute2)->currentValue);
		float HealthMax = static_cast<int>(targetList3[0]->getAttribute(&attribute2)->maximumValue);

		// Get window size and local player
		Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
		Vec2 res = Game.getClientInstance()->getGuiData()->windowSize;
		LocalPlayer* player = Game.getClientInstance()->getCILocalPlayer();

		if (player != nullptr) {
			// Calculate the position and width of the target box
			Vec4 rectPos((res.x / 2.f) + (res.x / 20.f), (res.y / 2.f) + (res.y / 24.f), (res.x / 2.f) + (res.x / 6.f), (res.y / 2.f) + (res.y / 8.f));
			float rectWidth = rectPos.z - rectPos.x;

			// Counter for fade
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

			// Draw the background box
			{
				DrawUtils::fillRectangle(Vec4{positionX + 2.f, positionY + 1.f, rectPos.z + 1, rectPos.w + 1}, Mc_Color(0, 0, 0), counter / 340.33333f);
			}

			// Get the target's name, then remove line breaks
			std::string targetName = Utils::sanitize(targetList3[0]->getNameTag()->getText());
			targetName = targetName.substr(0, targetName.find('\n'));
			std::string HealthString = std::to_string(static_cast<int>(Health));
			std::string HealthMaxString = std::to_string(static_cast<int>(HealthMax));
			std::string distance = "Distance: " + std::to_string((int)(*targetList3[0]->getPos()).dist(*Game.getLocalPlayer()->getPos()));
			std::string healthDisplay = "Health: " + HealthString + "/" + HealthMaxString;
			std::string armor = "Armor: ";
			std::string absorptionDisplay;

			// Absorption Bar
			if (Absorption > 0) {
				std::string absorptionString = std::to_string(static_cast<int>(Absorption));
				absorptionDisplay = " Absorption: " + absorptionString;
				float absorptionBarWidth = (Absorption / HealthMax) * rectWidth;
				if (!(targetList3[0]->damageTime > 1))
					DrawUtils::fillRectangle(Vec4(positionX + 3.f, rectPos.y + (res.y / 18.f), rectPos.x + absorptionBarWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), Mc_Color(255, 255, 85), counter / 100.f);
				else
					DrawUtils::fillRectangle(Vec4(positionX + 3.f, rectPos.y + (res.y / 18.f), rectPos.x + absorptionBarWidth, rectPos.y + (res.y / 18.f) + ((rectPos.w - (rectPos.y + (res.y / 18.f))) / 2)), Mc_Color(255, 255, 0), counter / 100.f);
			}

			// Draw the text
			{
				DrawUtils::drawText(Vec2(positionX + 3.f, rectPos.y - 17.f + (res.y / 35.f)), &targetName, Mc_Color(255, 255, 255), 1.f, counter / 100.f);         // name
				DrawUtils::drawText(Vec2(positionX + 3.f, rectPos.y - 8.5f + (res.y / 35.f)), &distance, Mc_Color(255, 255, 255), 0.7f, counter / 100.f);          // distance
				DrawUtils::drawText(Vec2(positionX + 3.f, rectPos.y - 3.5f + (res.y / 35.f)), &healthDisplay, Mc_Color(255, 255, 255), 0.7f, counter / 100.f);     // health
				DrawUtils::drawText(Vec2(positionX + 3.f, rectPos.y - 3.5f + (res.y / 35.f)), &absorptionDisplay, Mc_Color(255, 255, 85), 0.7f, counter / 100.f);  // absorption
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
}*/
