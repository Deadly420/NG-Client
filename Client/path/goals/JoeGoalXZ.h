#pragma once

#include "JoeGoal.h"

class JoeGoalXZ : public JoeGoal{
private:
	Vector3i targetPos;
public:
	JoeGoalXZ(const Vector3i& targetPos);

	bool isInGoal(Vector3i pos) override;
	float getHeuristicEstimation(Vector3i pos) override;

	static float heuristicEstimation(Vector3i node, Vector3i target);
};
