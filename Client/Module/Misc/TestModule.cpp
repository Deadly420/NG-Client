#include "TestModule.h"
#include "../../../include/imgui/imgui.h"
#include "../../../Utils/Logger.h"
#include "../../../Utils/VoxelIntersector.h"
#include "../../../Utils/DrawUtils.h"
#include "../../../SDK/MatrixStack.h"
#include <deque>
#include <array>
#include <unordered_set>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>			//radians
#include <glm/ext/matrix_transform.hpp>		// perspective, translate, rotate
#include <glm/ext/matrix_relational.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../../../Utils/Json.hpp"
#include "../../path/JoePathFinder.h"
#include "../../path/JoeMovementController.h"
#include "../../path/goals/JoeGoal.h"
#include "../../path/goals/JoeGoalXZ.h"
#include "../../ImmediateGui.h"
#include <chrono>  // for std::this_thread::sleep_for()
#include <thread>
#include "../../../Memory/Hooks.h"
//#include "../../../Memory/SlimMem.h"
//#include "../../../Memory/GameData.cpp"
using json = nlohmann::json;


TestModule::TestModule() : Module(0x0, Category::MISC, "For testing purposes only!") {
	enum1.addEntry(EnumEntry("1", 1)).addEntry(EnumEntry("2", 2)).addEntry(EnumEntry("3", 3));
	registerFloatSetting("float1", &float1, 0, -10, 10);
	registerIntSetting("int1", &int1, 0, -10, 10);
	registerEnumSetting("Enum1", &enum1, 0);
	registerBoolSetting("bool1", &bool1, true);
}

TestModule::~TestModule() {
}

const char* TestModule::getModuleName() {
	return "TestModule";
}

bool TestModule::isFlashMode() {
	return false;
}

void TestModule::onImGuiRender() {
	{
		// Hud
		auto ArrayListMod = moduleMgr->getModule<Arraylist>();
		auto TogglesSoundsMod = moduleMgr->getModule<ToggleSounds>();
		auto CustomFontMod = moduleMgr->getModule<FontChanger>();

		// Misc
		auto BreakerMod = moduleMgr->getModule<Breaker>();
		auto CrasherMod = moduleMgr->getModule<Crasher>();
		auto DerpMod = moduleMgr->getModule<Derp>();
		auto EditionFakerMod = moduleMgr->getModule<EditionFaker>();
		auto FreecamMod = moduleMgr->getModule<Freecam>();
		auto NoPacketMod = moduleMgr->getModule<NoPacket>();
		auto OffhandAllowMod = moduleMgr->getModule<OffhandAllow>();
		auto SpammerMod = moduleMgr->getModule<Spammer>();
		auto TeleportMod = moduleMgr->getModule<Teleport>();
		auto TimerMod = moduleMgr->getModule<Timer>();
		auto VanillaPlusMod = moduleMgr->getModule<VanillaPlus>();

		// Main Window
		ImGuiStyle* style = &ImGui::GetStyle();

		style->WindowPadding = ImVec2(15, 15);
		style->WindowRounding = 10.f;
		style->FramePadding = ImVec2(5, 5);
		style->FrameRounding = 6.f;
		style->ItemSpacing = ImVec2(12, 8);
		style->ItemInnerSpacing = ImVec2(8, 6);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 15.0f;
		style->ScrollbarRounding = 9.0f;
		style->GrabMinSize = 5.0f;
		style->GrabRounding = 3.0f;
		style->WindowTitleAlign = ImVec2(0.5, 0.5);

		style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
		style->Colors[ImGuiCol_Separator] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
		style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);

		ImGuiWindowFlags TargetFlags;
		TargetFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;

		if (ImGui::Begin("ClickGui", 0, TargetFlags)) {
			ImGui::SetWindowSize(ImVec2(360.f, 330.f));

			if (ImGui::CollapsingHeader("Combat")) {
				ImGui::Spacing();
				if (ImGui::Button("Test")) {
					// Handle button click action here
				}
				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Render")) {
				ImGui::Spacing();
				if (ImGui::Button("Test")) {
					// Handle button click action here
				}
				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Movement")) {
				ImGui::Spacing();
				if (ImGui::Button("Test")) {
					// Handle button click action here
				}
				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Player")) {
				ImGui::Spacing();
				if (ImGui::Button("Test")) {
					// Handle button click action here
				}
				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("World")) {
				ImGui::Spacing();
				if (ImGui::Button("Test")) {
					// Handle button click action here
				}
				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Entity")) {
				ImGui::Spacing();
				if (ImGui::Button("Test")) {
					// Handle button click action here
				}
				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("HUD")) {
				ImGui::Spacing();

				auto toggleModState = [](bool currentState, const char* labelOn, const char* labelOff) {
					if (ImGui::Button(currentState ? labelOn : labelOff)) {
						currentState = !currentState;
					}
					return currentState;
				};

				ArrayListMod->setEnabled(toggleModState(ArrayListMod->isEnabled(), "ArrayList (ON)", "ArrayList (OFF)"));
				CustomFontMod->setEnabled(toggleModState(CustomFontMod->isEnabled(), "CustomFont (ON)", "CustomFont (OFF)"));
				TogglesSoundsMod->setEnabled(toggleModState(TogglesSoundsMod->isEnabled(), "TogglesSounds (ON)", "TogglesSounds (OFF)"));

				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Misc")) {
				ImGui::Spacing();

				auto toggleModState = [](bool currentState, const char* labelOn, const char* labelOff) {
					if (ImGui::Button(currentState ? labelOn : labelOff)) {
						currentState = !currentState;
					}
					return currentState;
				};
				BreakerMod->setEnabled(toggleModState(BreakerMod->isEnabled(), "Breaker (ON)", "Breaker (OFF)"));
				CrasherMod->setEnabled(toggleModState(CrasherMod->isEnabled(), "Crasher (ON)", "Crasher (OFF)"));
				DerpMod->setEnabled(toggleModState(DerpMod->isEnabled(), "Derp (ON)", "Derp (OFF)"));
				EditionFakerMod->setEnabled(toggleModState(EditionFakerMod->isEnabled(), "EditionFaker (ON)", "EditionFaker (OFF)"));
				FreecamMod->setEnabled(toggleModState(FreecamMod->isEnabled(), "Freecam (ON)", "Freecam (OFF)"));
				NoPacketMod->setEnabled(toggleModState(NoPacketMod->isEnabled(), "NoPacket (ON)", "NoPacket (OFF)"));
				OffhandAllowMod->setEnabled(toggleModState(OffhandAllowMod->isEnabled(), "OffhandAllow (ON)", "OffhandAllow (OFF)"));
				SpammerMod->setEnabled(toggleModState(SpammerMod->isEnabled(), "Spammer (ON)", "Spammer (OFF)"));
				TeleportMod->setEnabled(toggleModState(TeleportMod->isEnabled(), "Teleport (ON)", "Teleport (OFF)"));
				TimerMod->setEnabled(toggleModState(TimerMod->isEnabled(), "Timer (ON)", "Timer (OFF)"));
				VanillaPlusMod->setEnabled(toggleModState(VanillaPlusMod->isEnabled(), "Vanilla+ (ON)", "Vanilla+ (OFF)"));

				ImGui::Spacing();
			}
		}
		ImGui::End();
	}
}

void TestModule::onEnable() {
	LocalPlayer* player = Game.getLocalPlayer();
	Inventory* inv = player->getSupplies()->inventory;
	if (player != nullptr) {
	}
	//PlayerHotbarPacket packet;
	//packet = PlayerHotbarPacket(1, 10, false);
	//Game.getClientInstance()->loopbackPacketSender->sendToServer(&packet);
}

void TestModule::onTick(GameMode* gm) {
}

void TestModule::onMove(MoveInputHandler* hand){
}

void TestModule::onPreRender(MinecraftUIRenderContext* renderCtx) {
	/* LocalPlayer* player = Game.getLocalPlayer();
	Inventory* inv = player->getSupplies()->inventory;
	Vec2 pos = Vec2(Game.getGuiData()->heightReal, Game.getGuiData()->widthReal);
	pos.x / 2.55;
	pos.y / 2.55;
	if (player != nullptr) {
		for (int i = 0; i <= 35; i++) {
			ItemStack* item = inv->getItemStack(i);
			//if (item->item != nullptr) {
				//std::string itemName = TextHolder(item->getItem()->name).getText();
				DrawUtils::drawItem(item, pos, 10.f, 1.f, false);
				pos.x += 20;
			}
		}
	}
	if (HorionGui.Button("Test Button", Vec2(200, 200), true)) {  // Check if button is pressed. When it gets pressed it sends the message.
		clientMessageF("Test Button Was Clicked");
	}*/
}

void TestModule::onPostRender(MinecraftUIRenderContext* renderCtx) {
}

void TestModule::onSendPacket(Packet* p) {
	if (p->isInstanceOf<PlayerHotbarPacket>()) {
		PlayerHotbarPacket* packet = reinterpret_cast<PlayerHotbarPacket*>(p);
		//packet->dimension = 1;
		//logF("%i", packet->numTransactions);
	}
}

void TestModule::onSendClientPacket(Packet* p) {
	if (p->isInstanceOf<PlayerHotbarPacket>()) {
		PlayerHotbarPacket* packet = reinterpret_cast<PlayerHotbarPacket*>(p);
		//packet->dimension = 1;
		//logF("%s", packet->name);
	}
}

void TestModule::onDisable() {
}

void TestModule::onLevelRender() {
}

void TestModule::onKey(int key, bool isDown, bool& cancel) {
	//Cancel W key for testing to make sure this works
	//if (key == 'W' && isDown) cancel = true;
}