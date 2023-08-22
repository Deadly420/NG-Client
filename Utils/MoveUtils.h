#pragma once
#include "../Memory/GameData.h"

class MoveUtil {
public:
	static void freeze(Vec3 initPos, bool damageTime);
	static void fullStop(bool damageTime);
	static void stop(bool damageTime);

	static void setSpeed(float speed);
	static bool keyPressed();
	static bool isMoving();
};