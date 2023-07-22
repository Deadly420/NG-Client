#include "JoeGoalXYZ.h"
bool JoeGoalXYZ::isInGoal(Vector3i pos) {
	return pos == targetPos;
}
float JoeGoalXYZ::getHeuristicEstimation(Vector3i pos) {
	return JoeGoalXZ::heuristicEstimation(pos, targetPos) + JoeGoalY::heuristicEstimation(pos, (float)targetPos.y);
}
JoeGoalXYZ::JoeGoalXYZ(const Vector3i& targetPos) : targetPos(targetPos) {}
