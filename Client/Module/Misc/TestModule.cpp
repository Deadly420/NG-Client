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
		// Hud - DONE
		auto TogglesSoundsMod = moduleMgr->getModule<ToggleSounds>();
		auto CustomFontMod = moduleMgr->getModule<FontChanger>();
		auto ArrayListMod = moduleMgr->getModule<Arraylist>();

		// Misc - DONE
		auto OffhandAllowMod = moduleMgr->getModule<OffhandAllow>();
		auto EditionFakerMod = moduleMgr->getModule<EditionFaker>();
		auto VanillaPlusMod = moduleMgr->getModule<VanillaPlus>();
		auto TeleportMod = moduleMgr->getModule<Teleport>();
		auto NoPacketMod = moduleMgr->getModule<NoPacket>();
		auto SpammerMod = moduleMgr->getModule<Spammer>();
		auto FreecamMod = moduleMgr->getModule<Freecam>();
		auto CrasherMod = moduleMgr->getModule<Crasher>();
		auto BreakerMod = moduleMgr->getModule<Breaker>();
		auto TimerMod = moduleMgr->getModule<Timer>();
		auto DerpMod = moduleMgr->getModule<Derp>();

		// Entity - DONE
		auto EntityLongJumpMod = moduleMgr->getModule<EntityLongJump>();
		auto EntitySpiderMod = moduleMgr->getModule<EntitySpider>();
		auto EntityJesusMod = moduleMgr->getModule<EntityJesus>();
		auto EntitySpeedMod = moduleMgr->getModule<EntitySpeed>();
		auto EntityBhopMod = moduleMgr->getModule<EntityBhop>();
		auto EntityFlyMod = moduleMgr->getModule<EntityFly>();

		// World - DONE
		auto PacketLoggerMod = moduleMgr->getModule<PacketLogger>();  // Debug
		auto InstaBreakMod = moduleMgr->getModule<InstaBreak>();
		auto ScaffoldMod = moduleMgr->getModule<Scaffold>();
		auto DisablerMod = moduleMgr->getModule<Disabler>();
		auto TowerMod = moduleMgr->getModule<Tower>();
		auto NukerMod = moduleMgr->getModule<Nuker>();

		// Player - DONE
		auto StackableItemMod = moduleMgr->getModule<StackableItem>();
		auto InvCleanerMod = moduleMgr->getModule<InventoryCleaner>();
		auto ChestStealerMod = moduleMgr->getModule<ChestStealer>();
		auto BlockReachMod = moduleMgr->getModule<BlockReach>();
		auto NoFriendsMod = moduleMgr->getModule<NoFriends>();
		auto ChestAuraMod = moduleMgr->getModule<ChestAura>();
		auto AutoArmorMod = moduleMgr->getModule<AutoArmor>();
		auto MidClickMod = moduleMgr->getModule<MidClick>();
		auto NoSwingMod = moduleMgr->getModule<NoSwing>();
		auto AntiBotMod = moduleMgr->getModule<AntiBot>();
		auto NoFallMod = moduleMgr->getModule<NoFall>();
		auto BlinkMod = moduleMgr->getModule<Blink>();
		auto XPMod = moduleMgr->getModule<XP>();

		// Movement - DONE
		auto AntiImmobileMod = moduleMgr->getModule<AntiImmobile>();
		auto AirJumpMod = moduleMgr->getModule<AirJump>();
		auto AirSwimMod = moduleMgr->getModule<AirSwim>();
		auto AutoSprintMod = moduleMgr->getModule<AutoSprint>();
		auto AntiVoidMod = moduleMgr->getModule<AntiVoid>();
		auto AutoSneakMod = moduleMgr->getModule<AutoSneak>();
		auto BhopMod = moduleMgr->getModule<Bhop>();
		auto FollowPathMod = moduleMgr->getModule<FollowPathModule>();
		auto FastStopMod = moduleMgr->getModule<FastStop>();
		auto FastLadderMod = moduleMgr->getModule<FastLadder>();
		auto FlyMod = moduleMgr->getModule<Fly>();
		auto GlideMod = moduleMgr->getModule<Glide>();
		auto HighJumpMod = moduleMgr->getModule<HighJump>();
		auto InvMoveMod = moduleMgr->getModule<InventoryMove>();
		auto JesusMod = moduleMgr->getModule<Jesus>();
		auto NoSlowdownMod = moduleMgr->getModule<NoSlowDown>();
		auto NoWebMod = moduleMgr->getModule<NoWeb>();
		auto PhaseMod = moduleMgr->getModule<Phase>();
		auto SpiderMod = moduleMgr->getModule<Spider>();
		auto SpeedMod = moduleMgr->getModule<Speed>();
		auto StepMod = moduleMgr->getModule<Step>();
		auto TwerkMod = moduleMgr->getModule<Twerk>();
		auto VelocityMod = moduleMgr->getModule<Velocity>();

		// Render - DONE
		auto CustomSkyMod = moduleMgr->getModule<RainbowSky>();
		auto CompassMod = moduleMgr->getModule<Compass>();
		auto ESPMod = moduleMgr->getModule<ESP>();
		auto FullBrightMod = moduleMgr->getModule<FullBright>();
		auto FreelookMod = moduleMgr->getModule<Freelook>();
		auto HUDMod = moduleMgr->getModule<HudModule>();
		auto MincecraftRGBMod = moduleMgr->getModule<MinecraftRGB>();
		auto NightModeMod = moduleMgr->getModule<NightMode>();
		auto NoHurtCamMod = moduleMgr->getModule<NoHurtcam>();
		auto NameTagsMod = moduleMgr->getModule<NameTags>();
		auto RadarMod = moduleMgr->getModule<Radar>();
		auto StorageESPMod = moduleMgr->getModule<StorageESP>();
		auto TracerMod = moduleMgr->getModule<Tracer>();
		auto TimeChangerMod = moduleMgr->getModule<TimeChanger>();
		auto ViewModelMod = moduleMgr->getModule<ViewModel>();
		auto WaypointsMod = moduleMgr->getModule<Waypoints>();
		auto XrayMod = moduleMgr->getModule<Xray>();
		auto ZoomMod = moduleMgr->getModule<Zoom>();

		// Combat - DONE
		auto CrystalAuraMod = moduleMgr->getModule<CrystalAura>();
		auto AutoClickerMod = moduleMgr->getModule<AutoClicker>();
		auto BowAimbotMod = moduleMgr->getModule<BowAimbot>();
		auto AutoTotemMod = moduleMgr->getModule<AutoTotem>();
		auto KillauraMod = moduleMgr->getModule<Killaura>();
		auto FastBowMod = moduleMgr->getModule<FastUse>();
		auto AutoPotMod = moduleMgr->getModule<AutoPot>();
		auto HitboxMod = moduleMgr->getModule<Hitbox>();
		auto AimbotMod = moduleMgr->getModule<Aimbot>();
		auto TeamsMod = moduleMgr->getModule<Teams>();
		auto ReachMod = moduleMgr->getModule<Reach>();

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
		TargetFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

		if (ImGui::Begin("NG Client", 0, TargetFlags)) {
			ImGui::SetWindowSize(ImVec2(360.f, 330.f));

			auto toggleModState = [](bool currentState, const char* labelOn, const char* labelOff) {
				if (ImGui::Button(currentState ? labelOn : labelOff)) {
					currentState = !currentState;
				}
				return currentState;
			};

			if (ImGui::CollapsingHeader("Combat")) {
				CrystalAuraMod->setEnabled(toggleModState(CrystalAuraMod->isEnabled(), "CrystalAura (ON)", "CrystalAura (OFF)"));
				AutoClickerMod->setEnabled(toggleModState(AutoClickerMod->isEnabled(), "AutoClicker (ON)", "AutoClicker (OFF)"));
				BowAimbotMod->setEnabled(toggleModState(BowAimbotMod->isEnabled(), "BowAimbot (ON)", "BowAimbot (OFF)"));
				AutoTotemMod->setEnabled(toggleModState(AutoTotemMod->isEnabled(), "AutoTotem (ON)", "AutoTotem (OFF)"));
				KillauraMod->setEnabled(toggleModState(KillauraMod->isEnabled(), "Killaura (ON)", "Killaura (OFF)"));
				FastBowMod->setEnabled(toggleModState(FastBowMod->isEnabled(), "Fast Bow (ON)", "Fast Bow (OFF)"));
				CrasherMod->setEnabled(toggleModState(CrasherMod->isEnabled(), "Crasher (ON)", "Crasher (OFF)"));
				AutoPotMod->setEnabled(toggleModState(AutoPotMod->isEnabled(), "AutoPot (ON)", "AutoPot (OFF)"));
				HitboxMod->setEnabled(toggleModState(HitboxMod->isEnabled(), "Hitbox (ON)", "Hitbox (OFF)"));
				AimbotMod->setEnabled(toggleModState(AimbotMod->isEnabled(), "Aimbot (ON)", "Aimbot (OFF)"));
				TeamsMod->setEnabled(toggleModState(TeamsMod->isEnabled(), "Teams (ON)", "Teams (OFF)"));
				ReachMod->setEnabled(toggleModState(ReachMod->isEnabled(), "Reach (ON)", "Reach (OFF)"));
				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Render")) {
				MincecraftRGBMod->setEnabled(toggleModState(MincecraftRGBMod->isEnabled(), "Mincecraft-RGB (ON)", "Mincecraft-RGB (OFF)"));
				TimeChangerMod->setEnabled(toggleModState(TimeChangerMod->isEnabled(), "TimeChanger (ON)", "TimeChanger (OFF)"));
				StorageESPMod->setEnabled(toggleModState(StorageESPMod->isEnabled(), "Storage-ESP (ON)", "Storage-ESP (OFF)"));
				FullBrightMod->setEnabled(toggleModState(FullBrightMod->isEnabled(), "FullBright (ON)", "FullBright (OFF)"));
				CustomSkyMod->setEnabled(toggleModState(CustomSkyMod->isEnabled(), "CustomSky (ON)", "CustomSky (OFF)"));
				WaypointsMod->setEnabled(toggleModState(WaypointsMod->isEnabled(), "Waypoints (ON)", "Waypoints (OFF)"));
				NoHurtCamMod->setEnabled(toggleModState(NoHurtCamMod->isEnabled(), "NoHurtCam (ON)", "NoHurtCam (OFF)"));
				ViewModelMod->setEnabled(toggleModState(ViewModelMod->isEnabled(), "ViewModel (ON)", "ViewModel (OFF)"));
				NightModeMod->setEnabled(toggleModState(NightModeMod->isEnabled(), "NightMode (ON)", "NightMode (OFF)"));
				NameTagsMod->setEnabled(toggleModState(NameTagsMod->isEnabled(), "NameTags (ON)", "NameTags (OFF)"));
				FreelookMod->setEnabled(toggleModState(FreelookMod->isEnabled(), "Freelook (ON)", "Freelook (OFF)"));
				CompassMod->setEnabled(toggleModState(CompassMod->isEnabled(), "Compass (ON)", "Compass (OFF)"));
				TracerMod->setEnabled(toggleModState(TracerMod->isEnabled(), "Tracer (ON)", "Tracer (OFF)"));
				RadarMod->setEnabled(toggleModState(RadarMod->isEnabled(), "Radar (ON)", "Radar (OFF)"));
				ZoomMod->setEnabled(toggleModState(ZoomMod->isEnabled(), "Zoom (ON)", "Zoom (OFF)"));
				XrayMod->setEnabled(toggleModState(XrayMod->isEnabled(), "Xray (ON)", "Xray (OFF)"));
				HUDMod->setEnabled(toggleModState(HUDMod->isEnabled(), "HUD (ON)", "HUD (OFF)"));
				ESPMod->setEnabled(toggleModState(ESPMod->isEnabled(), "ESP (ON)", "ESP (OFF)"));
				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Movement")) {
				AntiImmobileMod->setEnabled(toggleModState(AntiImmobileMod->isEnabled(), "Anti-Immobile (ON)", "Anti-Immobile (OFF)"));
				NoSlowdownMod->setEnabled(toggleModState(NoSlowdownMod->isEnabled(), "NoSlowdown (ON)", "NoSlowdown (OFF)"));
				FastLadderMod->setEnabled(toggleModState(FastLadderMod->isEnabled(), "FastLadder (ON)", "FastLadder (OFF)"));
				FollowPathMod->setEnabled(toggleModState(FollowPathMod->isEnabled(), "FollowPath (ON)", "FollowPath (OFF)"));
				AutoSprintMod->setEnabled(toggleModState(AutoSprintMod->isEnabled(), "AutoSprint (ON)", "AutoSprint (OFF)"));
				AutoSneakMod->setEnabled(toggleModState(AutoSneakMod->isEnabled(), "AutoSneak (ON)", "AutoSneak (OFF)"));
				HighJumpMod->setEnabled(toggleModState(HighJumpMod->isEnabled(), "HighJump (ON)", "HighJump (OFF)"));
				FastStopMod->setEnabled(toggleModState(FastStopMod->isEnabled(), "FastStop (ON)", "FastStop (OFF)"));
				AntiVoidMod->setEnabled(toggleModState(AntiVoidMod->isEnabled(), "Anti-Void (ON)", "Anti-Void (OFF)"));
				VelocityMod->setEnabled(toggleModState(VelocityMod->isEnabled(), "Velocity (ON)", "Velocity (OFF)"));
				InvMoveMod->setEnabled(toggleModState(InvMoveMod->isEnabled(), "InvMove (ON)", "InvMove (OFF)"));
				AirSwimMod->setEnabled(toggleModState(AirSwimMod->isEnabled(), "AirSwim (ON)", "AirSwim (OFF)"));
				AirJumpMod->setEnabled(toggleModState(AirJumpMod->isEnabled(), "AirJump (ON)", "AirJump (OFF)"));
				SpiderMod->setEnabled(toggleModState(SpiderMod->isEnabled(), "Spider (ON)", "Spider (OFF)"));
				NoWebMod->setEnabled(toggleModState(NoWebMod->isEnabled(), "NoWeb (ON)", "NoWeb (OFF)"));
				TwerkMod->setEnabled(toggleModState(TwerkMod->isEnabled(), "Twerk (ON)", "Twerk (OFF)"));
				SpeedMod->setEnabled(toggleModState(SpeedMod->isEnabled(), "Speed (ON)", "Speed (OFF)"));
				PhaseMod->setEnabled(toggleModState(PhaseMod->isEnabled(), "Phase (ON)", "Phase (OFF)"));
				JesusMod->setEnabled(toggleModState(JesusMod->isEnabled(), "Jesus (ON)", "Jesus (OFF)"));
				GlideMod->setEnabled(toggleModState(GlideMod->isEnabled(), "Glide (ON)", "Glide (OFF)"));
				StepMod->setEnabled(toggleModState(StepMod->isEnabled(), "Step (ON)", "Step (OFF)"));
				BhopMod->setEnabled(toggleModState(BhopMod->isEnabled(), "Bhop (ON)", "Bhop (OFF)"));
				FlyMod->setEnabled(toggleModState(FlyMod->isEnabled(), "Fly (ON)", "Fly (OFF)"));
				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Player")) {
				StackableItemMod->setEnabled(toggleModState(StackableItemMod->isEnabled(), "StackableItem (ON)", "StackableItem (OFF)"));
				InvCleanerMod->setEnabled(toggleModState(InvCleanerMod->isEnabled(), "InvCleaner (ON)", "Inv Cleaner (OFF)"));
				ChestStealerMod->setEnabled(toggleModState(ChestStealerMod->isEnabled(), "ChestStealer (ON)", "ChestStealer (OFF)"));
				BlockReachMod->setEnabled(toggleModState(BlockReachMod->isEnabled(), "BlockReach (ON)", "BlockReach (OFF)"));
				NoFriendsMod->setEnabled(toggleModState(NoFriendsMod->isEnabled(), "NoFriends (ON)", "NoFriends (OFF)"));
				ChestAuraMod->setEnabled(toggleModState(ChestAuraMod->isEnabled(), "ChestAura (ON)", "ChestAura (OFF)"));
				AutoArmorMod->setEnabled(toggleModState(AutoArmorMod->isEnabled(), "AutoArmor (ON)", "AutoArmor (OFF)"));
				MidClickMod->setEnabled(toggleModState(MidClickMod->isEnabled(), "MidClick (ON)", "MidClick (OFF)"));
				NoSwingMod->setEnabled(toggleModState(NoSwingMod->isEnabled(), "NoSwing (ON)", "NoSwing (OFF)"));
				AntiBotMod->setEnabled(toggleModState(AntiBotMod->isEnabled(), "Anti-Bot (ON)", "Anti-Bot (OFF)"));
				NoFallMod->setEnabled(toggleModState(NoFallMod->isEnabled(), "NoFall (ON)", "NoFall (OFF)"));
				BlinkMod->setEnabled(toggleModState(BlinkMod->isEnabled(), "Blink (ON)", "Blink (OFF)"));
				XPMod->setEnabled(toggleModState(XPMod->isEnabled(), "XP (ON)", "XP (OFF)"));
				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("World")) {
				PacketLoggerMod->setEnabled(toggleModState(PacketLoggerMod->isEnabled(), "PacketLogger (ON)", "PacketLogger (OFF)"));
				InstaBreakMod->setEnabled(toggleModState(InstaBreakMod->isEnabled(), "InstaBreak (ON)", "InstaBreak (OFF)"));
				ScaffoldMod->setEnabled(toggleModState(ScaffoldMod->isEnabled(), "Scaffold (ON)", "Scaffold (OFF)"));
				DisablerMod->setEnabled(toggleModState(DisablerMod->isEnabled(), "Disabler (ON)", "Disabler (OFF)"));
				TowerMod->setEnabled(toggleModState(TowerMod->isEnabled(), "Tower (ON)", "Tower (OFF)"));
				NukerMod->setEnabled(toggleModState(NukerMod->isEnabled(), "Nuker (ON)", "Nuker (OFF)"));
				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Entity")) {
				EntityLongJumpMod->setEnabled(toggleModState(EntityLongJumpMod->isEnabled(), "EntityLongJump (ON)", "EntityLongJump (OFF)"));
				EntitySpiderMod->setEnabled(toggleModState(EntitySpiderMod->isEnabled(), "EntitySpider (ON)", "Entity pider (OFF)"));
				EntityJesusMod->setEnabled(toggleModState(EntityJesusMod->isEnabled(), "EntityJesus (ON)", "EntityJesus (OFF)"));
				EntitySpeedMod->setEnabled(toggleModState(EntitySpeedMod->isEnabled(), "EntitySpeed (ON)", "EntitySpeed (OFF)"));
				EntityBhopMod->setEnabled(toggleModState(EntityBhopMod->isEnabled(), "EntityBhop (ON)", "EntityBhop (OFF)"));
				EntityFlyMod->setEnabled(toggleModState(EntityFlyMod->isEnabled(), "EntityFly (ON)", "EntityFly (OFF)"));
				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("HUD")) {
				TogglesSoundsMod->setEnabled(toggleModState(TogglesSoundsMod->isEnabled(), "TogglesSounds (ON)", " TogglesSounds (OFF)"));
				CustomFontMod->setEnabled(toggleModState(CustomFontMod->isEnabled(), "CustomFont (ON)", " CustomFont (OFF)"));
				ArrayListMod->setEnabled(toggleModState(ArrayListMod->isEnabled(), "ArrayList (ON)", " ArrayList (OFF)"));

				ImGui::Spacing();
			}

			if (ImGui::CollapsingHeader("Misc")) {
				OffhandAllowMod->setEnabled(toggleModState(OffhandAllowMod->isEnabled(), "Offhand Allow (ON)", "Offhand Allow (OFF)"));
				EditionFakerMod->setEnabled(toggleModState(EditionFakerMod->isEnabled(), "Edition Faker (ON)", "Edition Faker (OFF)"));
				VanillaPlusMod->setEnabled(toggleModState(VanillaPlusMod->isEnabled(), "Vanilla Plus (ON)", "Vanilla Plus (OFF)"));
				TeleportMod->setEnabled(toggleModState(TeleportMod->isEnabled(), "Teleport (ON)", "Teleport (OFF)"));
				NoPacketMod->setEnabled(toggleModState(NoPacketMod->isEnabled(), "No Packet (ON)", "No Packet (OFF)"));
				SpammerMod->setEnabled(toggleModState(SpammerMod->isEnabled(), "Spammer (ON)", "Spammer (OFF)"));
				FreecamMod->setEnabled(toggleModState(FreecamMod->isEnabled(), "Freecam (ON)", "Freecam (OFF)"));
				CrasherMod->setEnabled(toggleModState(CrasherMod->isEnabled(), "Crasher (ON)", "Crasher (OFF)"));
				BreakerMod->setEnabled(toggleModState(BreakerMod->isEnabled(), "Breaker (ON)", "Breaker (OFF)"));
				TimerMod->setEnabled(toggleModState(TimerMod->isEnabled(), "Timer (ON)", "Timer (OFF)"));
				DerpMod->setEnabled(toggleModState(DerpMod->isEnabled(), "Derp (ON)", "Derp (OFF)"));
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