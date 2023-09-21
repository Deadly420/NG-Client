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
	TargetFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;



	float yot = Game.getGuiData()->windowSize.x;

	auto toggleModState = [](bool currentState, const char* modName) {
		if (ImGui::Button(currentState ? std::string(std::string(modName) + std::string(" (ON)")).c_str() : std::string(std::string(modName) + std::string(" (OFF)")).c_str())) {
			currentState = !currentState;
		}
		return currentState;
	};

	if (ImGui::Begin("Combat", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 200.f));
		ImGui::SetWindowPos(ImVec2(0.f, 0.f));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::COMBAT, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("Render", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 530.f));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::RENDER, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("Movement", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 530.f));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::MOVEMENT, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("Player", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 330.f));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::PLAYER, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("World", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 200.f));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::WORLD, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("Entity", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 220.f));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::ENTITY, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("HUD", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 200.f));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::HUD, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("Misc", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 430.f));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::MISC, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}
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