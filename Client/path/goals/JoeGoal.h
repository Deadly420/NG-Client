#pragma once

#include "../../../Utils/HMath.h"

class JoeGoal {
private:
public:
	virtual ~JoeGoal();

	virtual bool isInGoal(Vector3i pos) = 0;
	virtual float getHeuristicEstimation(Vector3i pos) = 0;
};
