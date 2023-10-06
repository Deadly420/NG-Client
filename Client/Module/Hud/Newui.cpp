#include "Newui.h"
#include "../../../include/animations/snowflake.hpp"
#include "../../../include/imgui/imgui.h"
#include "../../../Utils/Utils.h"
#include "../../Manager/ModuleManager.h"

// Amimation Stuff
#include "../../../include/animations/fade.hpp"
#include "../../../include/animations/snowflake.hpp"
#include "../../../include/animations/dotMatrix.h"

NewUI::NewUI() : Module(VK_INSERT, Category::HUD, "ImGui (Dx12-DX11)") {
}

NewUI::~NewUI() {
}

const char* NewUI::getModuleName() {
	return "ImGui";
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

void NewUI::renderTooltip(std::string* text) {
	Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
	Vec2 currentTooltipPos = Vec2(5.f, windowSize.y - 15.f);
	ImVec2 textPos = ImVec2(currentTooltipPos.x, currentTooltipPos.y);
	ImVec4 rectPos = ImVec4(currentTooltipPos.x - 2.f, currentTooltipPos.y - 2.f, currentTooltipPos.x + 2.f, currentTooltipPos.y + 2.f);
	ImVec4 rectPosbottom = ImVec4(currentTooltipPos.x - 2.f, currentTooltipPos.y + 10.f, currentTooltipPos.x + 2.f, currentTooltipPos.y + 2.f);

	// DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);         // tooltips
	// DrawUtils::drawBoxBottom(rectPosbottom, Mc_Color(184, 0, 255), 1, 0.5);  // tooltips
	// DrawUtils::drawText(textPos, text, Mc_Color(0, 246, 255), textSize);     // tooltips
}

void getModuleListByCategoryName(Category category, std::vector<std::shared_ptr<Module>>* modList) {
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<Module>>* moduleList = moduleMgr->getModuleList();

	for (auto& it : *moduleList) {
		if (it->getCategory() == category)
			modList->push_back(it);
	}
}

// Snow Shit
#define SNOW_LIMIT 1  // max ammount of Snow/Bubbles allowed on screen at once
std::vector<Snowflake::Snowflake> snow;
std::vector<Particle> dots;

void NewUI::onImGuiRender() {
	// Main Window
	ImGuiStyle* style = &ImGui::GetStyle();
  
	style->Alpha = 1.0f;
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
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
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
	TargetFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;

	// Snowflakes
	POINT mouse;
	RECT rc = {0};
	md::FadeInOut fade;
	Snowflake::CreateSnowFlakes(snow, SNOW_LIMIT, 5.f /*minimum size*/, 25.f /*maximum size*/, 0 /*imgui window x position*/, 0 /*imgui window y position*/, Utils::getScreenResolution().x, Utils::getScreenResolution().y, Snowflake::vec3(0.f, 0.005f) /*gravity*/, IM_COL32(255, 255, 255, 100) /*color*/);
	auto window = (HWND)FindWindowA(nullptr, (LPCSTR) "Minecraft");

	RECT rect;
	GetWindowRect(window, &rect);
	ImVec2 size69 = ImVec2(rect.right - rect.left, rect.bottom - rect.top);

	if (ImGui::doSnow) {
		ImGui::SetNextWindowPos(ImVec2(size69.x - size69.x, size69.y - size69.y), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(size69.x, size69.y));
		ImGui::SetNextWindowBgAlpha(0.f);  // Set to 0.25 for a nice background

		ImGui::Begin("HELLO!!!", 0, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
		{
			GetWindowRect(window, &rc);
			GetCursorPos(&mouse);
			// render this before anything else so it is the background
			Snowflake::Update(snow, Snowflake::vec3(mouse.x, mouse.y), Snowflake::vec3(rc.left, rc.top));  // you can change a few things inside the update function
		}
		ImGui::End();
	}

	auto toggleModState = [](bool currentState, const char* modName) {
		if (ImGui::Button(currentState ? std::string(std::string(modName) + std::string(" (ON)")).c_str() : std::string(std::string(modName) + std::string(" (OFF)")).c_str())) {
			currentState = !currentState;
		}
		return currentState;
	};

	if (ImGui::Begin("Combat", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 410.f));
		ImGui::SetWindowPos(ImVec2(100, 100));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::COMBAT, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("Render", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 630.f));
		ImGui::SetWindowPos(ImVec2(350, 100));

		ImGui::Toggle("Toggle Snow", &ImGui::doSnow);

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::RENDER, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("Movement", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 630.f));
		ImGui::SetWindowPos(ImVec2(600, 100));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::MOVEMENT, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("Player", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 410.f));
		ImGui::SetWindowPos(ImVec2(850, 100));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::PLAYER, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("World", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 200.f));
		ImGui::SetWindowPos(ImVec2(850, 530.f));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::WORLD, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("Entity", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 220.f));
		ImGui::SetWindowPos(ImVec2(1100, 100));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::ENTITY, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("HUD", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 200.f));
		ImGui::SetWindowPos(ImVec2(1100, 340));

		std::vector<std::shared_ptr<Module>> moduleList;
		getModuleListByCategoryName(Category::HUD, &moduleList);
		for (auto& mod : moduleList) {
			mod->setEnabled(toggleModState(mod->isEnabled(), mod->getModuleName()));
		}
		ImGui::End();
	}

	if (ImGui::Begin("Misc", 0, TargetFlags)) {
		ImGui::SetWindowSize(ImVec2(200.f, 430.f));
		ImGui::SetWindowPos(ImVec2(1350, 100));

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