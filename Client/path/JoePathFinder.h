#pragma once

#include <memory>

#include "../../SDK/BlockLegacy.h"
#include "../../Utils/HMath.h"
#include "JoeConstants.h"
#include "JoePath.h"
#include "JoeSegment.h"
#include "goals/JoeGoal.h"

class JoePathFinder {
private:
	Vec3i startPos;
	JoePath currentPath;
	BlockSource* region;
	std::shared_ptr<JoeGoal> goal;

public:
	bool terminateSearch = false;
	float pathSearchTimeout = 5.f;

	JoePathFinder(Vec3i start, BlockSource* reg, std::shared_ptr<JoeGoal> goal);

	JoePath findPath();
	const JoePath& getCurrentPath() const;
};
