#pragma once
#include "../Module.h"
#include "../../Manager/ModuleManager.h"
#include "../../../include/imgui/imgui.h"

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
		if (ImGui && Game.getLocalPlayer() != nullptr || GameData::canUseMoveKeys() || Game.getRakNetConnector()->isonaServer()) {
			static ImVec2 windowPos = ImVec2(0, 300);
			ImGui::SetNextWindowPos(windowPos, ImGuiCond_FirstUseEver);

			if (ImGui::Begin("ServerInfo", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground)) {
				auto Server = Game.getRakNetConnector();
				if (Server == nullptr) return;

				std::string serverIp = Server->serverIp.getText();
				std::string numericalIp = Server->numericalIp.getText();
				std::string Port = std::to_string(Server->serverPort).c_str();

				if (Server->serverIp.getTextLength() < 1) {
					std::string ServerText = "Local World";
					ImVec2 textSize = ImGui::CalcTextSize(ServerText.c_str());
					ImGui::SetWindowSize(ImVec2(150, 40));
					ImGui::Text("%s", ServerText.c_str());
					ImGui::End();
				} else {
					std::string ServerText = "IP: " + serverIp + " \nPort: " + Port;
					ImVec2 textSize = ImGui::CalcTextSize(ServerText.c_str());
					ImGui::SetWindowSize(ImVec2(240, 60));
					ImGui::SetWindowFontScale(1.0);
					ImGui::Text("%s", ServerText.c_str());
					ImGui::End();
				}
			}
		}
	}

	void onPostRender(MinecraftUIRenderContext* renderCtx) {
		if (!ImGui) {
			if (Game.getLocalPlayer() != nullptr || GameData::canUseMoveKeys() || Game.getRakNetConnector()->isonaServer()) {
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