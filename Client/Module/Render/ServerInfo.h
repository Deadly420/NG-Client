#pragma once
#include "../Module.h"
#include "../../Manager/ModuleManager.h"
class ServerInfo : public Module {
public:
	float scale = 1.f;
	float serverInfoX = 0.f;
	float serverInfoY = 300.5f;

	ServerInfo() : Module(0x0, Category::RENDER, "shows the server ip and port of the current server") {
		registerFloatSetting("Pos-X", &serverInfoX, serverInfoX, 0.0f, Game.getClientInstance()->getGuiData()->windowSize.x, "Pos-X: Set the horizontal position from 0 to the window width");
		registerFloatSetting("Pos-Y", &serverInfoY, serverInfoY, 0.0f, Game.getClientInstance()->getGuiData()->windowSize.y, "Pos-Y: Set the vertical position from 0 to the window height");
		registerFloatSetting("Size", &scale, scale, 0.1f, 1.5f, "Size: Adjust the size from 0.1 to 1.5");
	};
	~ServerInfo(){};

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
					serverIp = "Local World", Port = "Local World";
				}
				std::string ServerText = "IP: " + serverIp + " \nPort: " + Port;

				DrawUtils::drawText(Vec2{textPos}, &ServerText, Mc_Color(255, 255, 255), scale);
			}
		}
	}

	virtual const char* getModuleName() override {
		return "ServerInfo";
	}
};