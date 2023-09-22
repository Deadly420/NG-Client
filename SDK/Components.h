#pragma once
#include "../Utils/HMath.h"
// The variable names in both of these 2 classes could be wrong I am not sure it shouldn't be hard to figure them out
struct ActorRotationComponent {
public:
	union {
		struct {
			float pitch;
			float yaw;
		};
		Vec2 rot;
	};
	union {
		struct {
			float prevPitch;
			float prevYaw;
		};
		Vec2 rotPrev;
	};
};

struct ActorHeadRotationComponent {
public:
	union {
		struct {
			float pitch;
			float yaw;
		};
		Vec2 rot;
	};
};

struct ActorGameTypeComponent {
public:
	int gameType;
};

struct FallDistanceComponent {
public:
	float fallDistance;
};

struct SwimSpeedMultiplierComponent {
public:
	float swimSpeedMultiplier;
};

struct RenderPositionComponent {
public:
	Vec3 renderPos;
};

struct RenderRotationComponent {
public:
	Vec2 renderRot;
};

struct AbilitiesComponent {
public:
	BUILD_ACCESS(this, bool, isFlying, 0x158);
	BUILD_ACCESS(this, bool, canFly, 0x164);
};

struct FlySpeedComponent {
public:
	float flySpeed; // it's more like in air speed then fly speed
};

struct RuntimeIDComponent {
public:
	int64_t runtimeID;
};

struct MaxAutoStepComponent {
public:
	float stepHeight;
};
