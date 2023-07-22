#pragma once

#include "JoeGoal.h"

class JoeGoalY : public JoeGoal {
private:
	float target;
public:
	JoeGoalY(float target);

	bool isInGoal(Vector3i pos) override;
	float getHeuristicEstimation(Vector3i pos) override;

	static float heuristicEstimation(Vector3i node, float target);
};
