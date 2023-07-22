#include "JoeGoalXZ.h"

#include "../JoeConstants.h"

bool JoeGoalXZ::isInGoal(Vector3i pos) {
	return pos.x == targetPos.x && pos.z == targetPos.z;
}
float JoeGoalXZ::getHeuristicEstimation(Vector3i pos) {
	return JoeGoalXZ::heuristicEstimation(targetPos, pos);
}
float JoeGoalXZ::heuristicEstimation(Vector3i node, Vector3i target) {
	Vector3i diff = node.sub(target);
	int x = abs(diff.x);
	int z = abs(diff.z);
	float straight;
	float diagonal;
	if (x < z) {
		straight = (float)z - x;
		diagonal = (float)x;
	} else {
		straight = (float)x - z;
		diagonal = (float)z;
	}
	static const float SQRT_2 = sqrtf(2);
	diagonal *= SQRT_2;
	return (straight + diagonal) / SPRINT_SPEED;
}
JoeGoalXZ::JoeGoalXZ(const Vector3i& targetPos) : targetPos(targetPos) {}
