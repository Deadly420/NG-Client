#pragma once

#include "JoeGoal.h"
#include "JoeGoalY.h"
#include "JoeGoalXZ.h"

class JoeGoalXYZ : public JoeGoal {
private:
	Vector3i targetPos;
public:
	JoeGoalXYZ(const Vector3i& targetPos);

	bool isInGoal(Vector3i pos) override;
	float getHeuristicEstimation(Vector3i pos) override;
};
