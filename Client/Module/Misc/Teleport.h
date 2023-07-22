#pragma once

#include "../Module.h"

class Teleport : public Module {
private:
	bool onlyHand = false;
	bool lerp = false;
	float lerpSpeed = 0.1f;
	bool hasClicked = false;
	bool shouldTP = false;
	Vector3 tpPos;

public:
	Teleport();
	~Teleport();

	// Inherited via Module
	virtual void onTick(GameMode* gm) override;
	virtual const char* getModuleName() override;
};