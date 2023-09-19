#include "Newui.h"
#include "../../../include/imgui/imgui.h"
#include "../ModuleManager.h"

NewUI::NewUI() : Module(VK_INSERT, Category::HUD, "New UI (Dx12)") {
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

void getModuleListByCategoryName(Category category, std::vector<std::shared_ptr<Module>>* modList) {
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<Module>>* moduleList = moduleMgr->getModuleList();

	for (auto& it : *moduleList) {
		if (it->getCategory() == category)
			modList->push_back(it);
	}
}

void NewUI::onImGuiRender() {
	// Hud
	auto TogglesSoundsMod = moduleMgr->getModule<ToggleSounds>();
	auto CustomFontMod = moduleMgr->getModule<FontChanger>();
	auto ArrayListMod = moduleMgr->getModule<Arraylist>();

	// Misc
	auto OffhandAllowMod = moduleMgr->getModule<OffhandAllow>();
	auto EditionFakerMod = moduleMgr->getModule<EditionFaker>();
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
	auto TargetHUDMod = moduleMgr->getModule<TargetHUD>();
	auto NameTagsMod = moduleMgr->getModule<NameTags>();
	auto FreelookMod = moduleMgr->getModule<Freelook>();
	auto CompassMod = moduleMgr->getModule<Compass>();
	auto TracerMod = moduleMgr->getModule<Tracer>();
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
	//ImGui::GetBackgroundDrawList()->AddText(ImVec2(100, 100), ImColor(0.f, 0.f, 1.f, 1.f), "Nigger");


	if (ImGui::Begin("NG Client", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(360.f, 330.f));

		auto toggleModState = [](bool currentState, const char* modName) {
			if (ImGui::Button(currentState ? std::string(std::string(modName) + std::string(" (ON)")).c_str() : std::string(std::string(modName) + std::string(" (OFF)")).c_str())) {
				currentState = !currentState;
			}
			return currentState;
		};

		if (ImGui::CollapsingHeader("Combat")) {
			std::vector<std::shared_ptr<Module>> moduleList;
			getModuleListByCategoryName(Category::COMBAT, &moduleList);
			for (auto& mod : moduleList) {
				mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
			}
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Render")) {
			std::vector<std::shared_ptr<Module>> moduleList;
			getModuleListByCategoryName(Category::RENDER, &moduleList);
			for (auto& mod : moduleList) {
				mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
			}
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Movement")) {
			std::vector<std::shared_ptr<Module>> moduleList;
			getModuleListByCategoryName(Category::MOVEMENT, &moduleList);
			for (auto& mod : moduleList) {
				mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
			}
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Player")) {
			std::vector<std::shared_ptr<Module>> moduleList;
			getModuleListByCategoryName(Category::PLAYER, &moduleList);
			for (auto& mod : moduleList) {
				mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
			}
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("World")) {
			std::vector<std::shared_ptr<Module>> moduleList;
			getModuleListByCategoryName(Category::WORLD, &moduleList);
			for (auto& mod : moduleList) {
				mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
			}
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Entity")) {
			std::vector<std::shared_ptr<Module>> moduleList;
			getModuleListByCategoryName(Category::ENTITY, &moduleList);
			for (auto& mod : moduleList) {
				mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
			}
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("HUD")) {
			std::vector<std::shared_ptr<Module>> moduleList;
			getModuleListByCategoryName(Category::HUD, &moduleList);
			for (auto& mod : moduleList) {
				mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
			}
			ImGui::Spacing();
		}

		if (ImGui::CollapsingHeader("Misc")) {
			std::vector<std::shared_ptr<Module>> moduleList;
			getModuleListByCategoryName(Category::MISC, &moduleList);
			for (auto& mod : moduleList) {
				mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
			}
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