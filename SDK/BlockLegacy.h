#pragma once

#include "../Utils/HMath.h"
#include "../Utils/Utils.h"
#include "TextHolder.h"
//#include "Tag.h"

class Material {
public:
	int type;  // 5 for water, 6 for lava
	bool isFlammable;
	bool isNeverBuildable;
	bool isAlwaysDestroyable;
	bool isReplaceable;
	bool isLiquid;  // 0x0008
private:
	char pad2[0x3];  // 0x009
public:
	float translucency;  // 0x00C
	bool isBlockingMotion;
	bool isBlockingPrecipitation;
	bool isSolid;
	bool isSuperHot;
	float color[4];
};

class Entity;
class Block;
class BlockSource;

class BlockLegacy {
public:
	uintptr_t** Vtable;         //0x0000
	class TextHolder tileName;  //0x0008
private:
	char pad_0028[8];  //0x0028
public:
	class TextHolder name;  //0x0030
private:
	char pad_0050[136];  //0x0050
public:
	class Material* material;  //0x00D8
private:
	char pad_00E0[108];  //0x00E0
public:
	short blockId;  //0x014C

	int liquidGetDepth(BlockSource*, const Vector3i* pos);
	void liquidGetFlow(Vector3* flowOut, BlockSource*, const Vector3i* pos);
	bool getCollisionShape(AABB* collShapeOut, Block* block, BlockSource* blockSource, const Vector3i* pos, Entity* actor);
	bool hasWater(BlockSource*, const Vector3i& pos);
};

class Block {
public:
	uint8_t data;  // 0x8

private:
	char pad[0x7];

public:
	BlockLegacy* blockLegacy;  // 0x10

	inline BlockLegacy* toLegacy() { return blockLegacy; }

	virtual ~Block();
	virtual int getRenderLayer();
};

class CompoundTag;

class BlockActor {
private:
	virtual void destructor();
	virtual __int64 load(__int64&, CompoundTag*, __int64&);

public:
	virtual bool save(CompoundTag*);
};

class BlockSource {
public:
	virtual void Destructor();
	virtual Block* getBlock(int, int, int);
	virtual Block* getBlock(Vector3i const&);
	virtual Block* getBlock(Vector3i const&, int);
	virtual BlockActor* getBlockEntity(Vector3i const&);
	virtual Block* getExtraBlock(Vector3i const&);
	virtual Block* getLiquidBlock(Vector3i const&);
	virtual bool hasBlock(Vector3i const&);
	virtual bool containsMaterial(AABB const&, struct MaterialType);
	virtual Material* getMaterial(Vector3i const&);
	virtual Material* getMaterial(int, int, int);
	virtual bool hasChunksAt(struct Bounds const&);
	virtual bool hasChunksAt(Vector3i const&, int);
	virtual bool hasChunksAt(AABB const&);
	virtual int getDimensionId(void);
	virtual __int64 getWeakRef(void);
	virtual void addListener(struct BlockSourceListener&);
	virtual void removeListener(BlockSourceListener&);
	virtual class EntityList* fetchEntities(Entity const*, AABB const&, bool);
	virtual class EntityList* fetchEntities(__int64, AABB const&, Entity const*);
	virtual void setBlock(Vector3i const&, Block const&, int, class ActorBlockSyncMessage const*, Entity*);
	virtual bool containsAnyLiquid(AABB const&);
	virtual int getMinHeight(void);
	virtual class Dimension* getDimension(void);
	virtual class Dimension* getDimensionConst(void);
	virtual __int64 getILevel(void);
	virtual std::vector<AABB>* fetchAABBs(AABB const&, bool);
	virtual std::vector<AABB>* fetchCollisionShapes(AABB const&, float*, bool, class IActorMovementProxy*);
	virtual AABB* getTallestCollisionShape(AABB const&, float*, bool, IActorMovementProxy*);
	virtual __int64 getChunkSource(void);
	virtual bool isSolidBlockingBlock(Vector3i const&);
};