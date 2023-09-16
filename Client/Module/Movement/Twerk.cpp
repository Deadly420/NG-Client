#include "Twerk.h"

Twerk::Twerk() : Module(0x0, Category::MOVEMENT, "Crouch Spam.") {
	registerFloatSetting("Delay", &delay, delay, 0.05f, 10, "The Delay For the Spam");
}

Twerk::~Twerk() {
}

const char* Twerk::getModuleName() {
	return ("Twerk");
}

void Twerk::onTick(GameMode* gm) {
	Odelay++;
	if (Odelay > delay * *Game.getClientInstance()->minecraft->simTimer) {
		Game.getClientInstance()->getMoveTurnInput()->isSneakDown = !Game.getClientInstance()->getMoveTurnInput()->isSneakDown;
		Odelay = 0;
	}
}