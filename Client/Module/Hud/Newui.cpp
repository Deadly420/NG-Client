#include "Newui.h"
#include "../../../include/imgui/imgui.h"
#include "../ModuleManager.h"

NewUI::NewUI() : Module(VK_INSERT, Category::HUD, "New UI") {
}

NewUI::~NewUI() {
}

const char* NewUI::getModuleName() {
	return "NewUI";
}

void NewUI::onEnable() {
	static auto clickGuiMod = moduleMgr->getModule<ClickGuiMod>();
	clickGuiMod->setEnabled(false);
	//Game.getClientInstance()->releaseMouse();
}

void NewUI::onDisable() {
	Game.getClientInstance()->grabMouse();
	Opacity = 0;
}

void NewUI::onPostRender(MinecraftUIRenderContext* renderCtx) {
	if (Opacity < 60)
	 	Opacity++;

	// Fill Background
	DrawUtils::fillRectangle(Vec4(0, 0, Game.getGuiData()->widthGame, Game.getGuiData()->heightGame), Mc_Color(0, 0, 0), Opacity / 100.f);
}

void NewUI::onImGuiRender() {
	// Hud
	auto TogglesSoundsMod = moduleMgr->getModule<ToggleSounds>();
	auto CustomFontMod = moduleMgr->getModule<FontChanger>();
	auto ArrayListMod = moduleMgr->getModule<Arraylist>();

	// Misc
	auto OffhandAllowMod = moduleMgr->getModule<OffhandAllow>();
	auto EditionFakerMod = moduleMgr->getModule<EditionFaker>();
	auto VanillaPlusMod = moduleMgr->getModule<VanillaPlus>();  // Debug
	auto TeleportMod = moduleMgr->getModule<Teleport>();
	auto NoPacketMod = moduleMgr->getModule<NoPacket>();
	auto SpammerMod = moduleMgr->getModule<Spammer>();
	auto FreecamMod = moduleMgr->getModule<Freecam>();
	auto CrasherMod = moduleMgr->getModule<Crasher>();
	auto BreakerMod = moduleMgr->getModule<Breaker>();
	auto TimerMod = moduleMgr->getModule<Timer>();
	auto DerpMod = moduleMgr->getModule<Derp>();

	// Entity
	auto EntityLongJumpMod = moduleMgr->getModule<EntityLongJump>();
	auto EntitySpiderMod = moduleMgr->getModule<EntitySpider>();
	auto EntityJesusMod = moduleMgr->getModule<EntityJesus>();
	auto EntitySpeedMod = moduleMgr->getModule<EntitySpeed>();
	auto EntityBhopMod = moduleMgr->getModule<EntityBhop>();
	auto EntityFlyMod = moduleMgr->getModule<EntityFly>();

	// World
	auto InstaBreakMod = moduleMgr->getModule<InstaBreak>();
	auto ScaffoldMod = moduleMgr->getModule<Scaffold>();
	auto DisablerMod = moduleMgr->getModule<Disabler>();
	auto TowerMod = moduleMgr->getModule<Tower>();
	auto NukerMod = moduleMgr->getModule<Nuker>();

	// Player
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

	// Movement
	auto FollowPathMod = moduleMgr->getModule<FollowPathModule>();
	auto AntiImmobileMod = moduleMgr->getModule<AntiImmobile>();
	auto NoSlowdownMod = moduleMgr->getModule<NoSlowDown>();
	auto InvMoveMod = moduleMgr->getModule<InventoryMove>();
	auto FastLadderMod = moduleMgr->getModule<FastLadder>();
	auto AutoSprintMod = moduleMgr->getModule<AutoSprint>();
	auto AutoSneakMod = moduleMgr->getModule<AutoSneak>();
	auto VelocityMod = moduleMgr->getModule<Velocity>();
	auto HighJumpMod = moduleMgr->getModule<HighJump>();
	auto FastStopMod = moduleMgr->getModule<FastStop>();
	auto AntiVoidMod = moduleMgr->getModule<AntiVoid>();
	auto AirSwimMod = moduleMgr->getModule<AirSwim>();
	auto AirJumpMod = moduleMgr->getModule<AirJump>();
	auto SpiderMod = moduleMgr->getModule<Spider>();
	auto TwerkMod = moduleMgr->getModule<Twerk>();
	auto SpeedMod = moduleMgr->getModule<Speed>();
	auto PhaseMod = moduleMgr->getModule<Phase>();
	auto NoWebMod = moduleMgr->getModule<NoWeb>();
	auto JesusMod = moduleMgr->getModule<Jesus>();
	auto GlideMod = moduleMgr->getModule<Glide>();
	auto StepMod = moduleMgr->getModule<Step>();
	auto BhopMod = moduleMgr->getModule<Bhop>();
	auto FlyMod = moduleMgr->getModule<Fly>();

	// Render
	auto MincecraftRGBMod = moduleMgr->getModule<MinecraftRGB>();
	auto TimeChangerMod = moduleMgr->getModule<TimeChanger>();
	auto StorageESPMod = moduleMgr->getModule<StorageESP>();
	auto FullBrightMod = moduleMgr->getModule<FullBright>();
	auto CustomSkyMod = moduleMgr->getModule<RainbowSky>();
	auto WaypointsMod = moduleMgr->getModule<Waypoints>();
	auto ViewModelMod = moduleMgr->getModule<ViewModel>();
	auto NoHurtCamMod = moduleMgr->getModule<NoHurtcam>();
	auto NightModeMod = moduleMgr->getModule<NightMode>();
	auto NameTagsMod = moduleMgr->getModule<NameTags>();
	auto FreelookMod = moduleMgr->getModule<Freelook>();
	auto CompassMod = moduleMgr->getModule<Compass>();
	auto TracerMod = moduleMgr->getModule<Tracer>();
	auto HUDMod = moduleMgr->getModule<HudModule>();
	auto RadarMod = moduleMgr->getModule<Radar>();
	auto ZoomMod = moduleMgr->getModule<Zoom>();
	auto XrayMod = moduleMgr->getModule<Xray>();
	auto ESPMod = moduleMgr->getModule<ESP>();

	// Combat
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

	style->WindowTitleAlign = ImVec2(0.5, 0.5);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->WindowPadding = ImVec2(15, 15);
	style->ItemSpacing = ImVec2(12, 8);
	style->FramePadding = ImVec2(5, 5);
	style->ScrollbarRounding = 9.0f;
	style->ScrollbarSize = 15.0f;
	style->IndentSpacing = 25.0f;
	style->WindowRounding = 10.f;
	style->GrabRounding = 3.0f;
	style->FrameRounding = 6.f;
	style->GrabMinSize = 5.0f;

	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_Separator] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);

	ImGuiWindowFlags TargetFlags;
	TargetFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;

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
			TogglesSoundsMod->setEnabled(toggleModState(TogglesSoundsMod->isEnabled(), "TogglesSounds (ON)", "TogglesSounds (OFF)"));
			CustomFontMod->setEnabled(toggleModState(CustomFontMod->isEnabled(), "CustomFont (ON)", "CustomFont (OFF)"));
			ArrayListMod->setEnabled(toggleModState(ArrayListMod->isEnabled(), "ArrayList (ON)", "ArrayList (OFF)"));
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

void NewUI::onKeyUpdate(int key, bool isDown) {
	static auto imgui = moduleMgr->getModule<NewUI>();

	switch (key) {
	case VK_ESCAPE:
		imgui->setEnabled(false);
		return;
	default:
		if (key == imgui->getKeybind())
			imgui->setEnabled(false);
	}
}