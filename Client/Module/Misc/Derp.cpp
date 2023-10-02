#include "Derp.h"

Derp::Derp() : Module(0x0, Category::MISC, "lol you stupid.") {
	registerBoolSetting("Have a stroke", &epicStroke, epicStroke, "ihaveastroke: Toggle epic stroke mode");
	registerBoolSetting("packet mode", &packetMode, packetMode, "packet mode: Toggle packet mode");
}

Derp::~Derp() {
}

const char* Derp::getModuleName() {
	return "Derp";
}

void Derp::onPlayerTick(Player* player) {
	if (Game.getLocalPlayer() != nullptr) {
		player->getActorRotationComponent()->rot.x = (counter % 360);  // free look player->getActorRotationComponent()->rot.y = (counter % 360);
		player->getActorHeadRotationComponent()->rot.x = (counter % 360);
		player->getMobBodyRotationComponent()->bodyRot = (counter % 360);
		// player->getMovementProxy()->setYHeadRot(counter % 360);

		if (counter < 360)
			counter += 30;
		else
			counter = 0;
	}
}
