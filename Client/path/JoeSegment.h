#pragma once

#include "../../Utils/HMath.h"
#include <vector>

enum JoeSegmentType{
	INVALID = -1,
	WALK = 0,
	JUMP,
	DROP,
	PARKOUR_JUMP_SINGLE,
	WATER_WALK
};

class JoeSegment {
private:
	JoeSegmentType segmentType;
	Vector3i start, end;
	float cost;
	bool allowSprint;
	std::vector<Vector3i> validPositions;
public:
	JoeSegment(JoeSegmentType type, Vector3i& start, Vector3i& stop, float cost, bool allowSprint = false);
	void draw();
	bool isAllowingSprint() const;
	void setAllowSprint(bool allowSprint);
	JoeSegmentType getSegmentType() const;
	const Vector3i& getStart() const;
	const Vector3i& getEnd() const;
	bool isInValidPosition(const Vector3i& pos) const;
	void setValidPositions(const std::vector<Vector3i>& validPositions);
	float getCost() const;
	void init();
};
