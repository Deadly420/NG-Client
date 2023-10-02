#pragma once
#include "../Module.h"
#include "../../Manager/ModuleManager.h"
class ServerInfo : public Module {
public:
	bool ImGui = false;
	float scale = 1.f;
	float serverInfoX = 0.f;
	float serverInfoY = 300.5f;

	ServerInfo() : Module(0x0, Category::RENDER, "shows the server ip and port of the current server") {
		registerBoolSetting("ImGui", &ImGui, ImGui, "Renders With ImGui");
		registerFloatSetting("Pos-X", &serverInfoX, serverInfoX, 0.0f, Game.getClientInstance()->getGuiData()->windowSize.x, "Pos-X: Set the horizontal position from 0 to the window width");
		registerFloatSetting("Pos-Y", &serverInfoY, serverInfoY, 0.0f, Game.getClientInstance()->getGuiData()->windowSize.y, "Pos-Y: Set the vertical position from 0 to the window height");
		registerFloatSetting("Size", &scale, scale, 0.1f, 1.5f, "Size: Adjust the size from 0.1 to 1.5");
	};
	~ServerInfo(){};

	void onImGuiRender() {
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
		if (ImGui) {
			if (ImGui::Begin("ServerInfo", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {
				ImGui::SetWindowPos(ImVec2(serverInfoX, serverInfoY));
				auto Server = Game.getRakNetConnector();
				if (Server == nullptr) return;

				std::string serverIp = Server->serverIp.getText();
				std::string numericalIp = Server->numericalIp.getText();
				std::string Port = std::to_string(Server->serverPort).c_str();

				if (Server->serverIp.getTextLength() < 1) {
					std::string ServerText = "Local World";
					ImVec2 textSize = ImGui::CalcTextSize(ServerText.c_str());
					ImGui::SetWindowSize(textSize);
					ImGui::Text("%s", ServerText.c_str());
					ImGui::End();
				} else {
					std::string ServerText = "IP: " + serverIp + " \nPort: " + Port;
					ImVec2 textSize = ImGui::CalcTextSize(ServerText.c_str());
					ImGui::SetWindowSize(textSize);
					ImGui::Text("%s", ServerText.c_str());
					ImGui::End();
				}
			}
		}
	}

	void onPostRender(MinecraftUIRenderContext* renderCtx) {
		if (!(Game.getLocalPlayer() == nullptr || !GameData::canUseMoveKeys())) {
			if (Game.getLocalPlayer() != nullptr || Game.getRakNetConnector()->isonaServer()) {
				auto Server = Game.getRakNetConnector();
				if (Server == nullptr) return;

				float yVal = serverInfoY;
				float xVal = serverInfoX;

				std::string serverIp = Server->serverIp.getText();
				std::string numericalIp = Server->numericalIp.getText();
				std::string Port = std::to_string(Server->serverPort).c_str();

				Vec2 textPos = Vec2(xVal, yVal);

				if (Server->serverIp.getTextLength() < 1) {
					std::string ServerText = "Local World";
					DrawUtils::drawText(Vec2{textPos}, &ServerText, Mc_Color(255, 255, 255), scale);
				} else {
					std::string ServerText = "IP: " + serverIp + " \nPort: " + Port;
					DrawUtils::drawText(Vec2{textPos}, &ServerText, Mc_Color(255, 255, 255), scale);
				}
			}
		}
	}

	virtual const char* getModuleName() override {
		return "ServerInfo";
	}
};