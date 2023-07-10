#pragma once

#include "Module.h"

class BlockReach : public Module {
private:
	float blockReach = 7.f;

public:
	BlockReach();
	~BlockReach();

	inline float getBlockReach() { return blockReach; };
	inline void setBlockReach(float reach) { blockReach = reach; };
	// Inherited via Module
	virtual const char* getModuleName() override;
};
