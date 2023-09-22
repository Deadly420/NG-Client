#pragma once

#include "Entity.h"
#include "GameSettingsInput.h"
#include "LoopbackPacketSender.h"
#include "MinecraftUIRenderContext.h"
#include "TextHolder.h"

class Minecraft {
private:
	char pad_0x0000[0xD8];  //0x0000
public:
	float* timer;       //0x00D8
	float* otherTimer;  //0x00E0

	void setTimerSpeed(float tps) {
		*this->timer = tps;
		*this->otherTimer = tps;
	}
};

class Tessellator;
class Block;

class BlockTessellator;
class ResourceLocation {
private:
	char pad[0x28];
	__int64 hashCode;  // 0x28
	char pad2[8];
};

class HashedString {
private:
	unsigned __int64 hash;
	TextHolder text;  // 0x0008

public:
	HashedString(const std::string& text) {
		this->text.setText(text);

		this->computeHash();
	}

	void computeHash() {
		hash = 0xCBF29CE484222325i64;
		if (this->text.getTextLength() <= 0)
			return;
		char* textP = this->text.getText();
		auto c = *textP;

		do {
			hash = hash * 0x100000001B3i64 ^ c;
			c = *++textP;
		} while (*textP);
	}

	unsigned __int64 getHash() {
		return this->hash;
	}
};

namespace mce {
class TextureGroup;
class MaterialPtr;
class Mesh {
public:
	void renderMesh(__int64 screenContext, mce::MaterialPtr* material, size_t numTextures, __int64** textureArray);

	template <size_t numTextures>
	void renderMesh(__int64 screenContext, mce::MaterialPtr* material, std::array<__int64*, numTextures> textures) {
		this->renderMesh(screenContext, material, numTextures, &textures[0]);
	}
};
class TexturePtr {
private:
	__int64* clientTexture;
	char pad[0x8];
	ResourceLocation resourceLocation;  // 0x10

public:
	__int64* getClientTexture() {
		return this->clientTexture;
	}
};
class MaterialPtr {
private:
	std::shared_ptr<void> materialPtr;

public:
	MaterialPtr(HashedString materialName, bool switchable = false);

	static MaterialPtr* createMaterial(HashedString materialName);
};
}  // namespace mce

class MaterialPtr {
private:
	char padding[0x138];

	BUILD_ACCESS(this, TextHolder, materialName, 0x18);
	BUILD_ACCESS(this, TextHolder*, materialNamePtr, 0x18);
	BUILD_ACCESS(this, __int64, testValue, 0x20);

public:
	BUILD_ACCESS(this, MaterialPtr*, ptrToSelf, 0x0);
	BUILD_ACCESS(this, __int64*, ptrToSelfClass, 0x8);

	// I have no fucking idea why there's sometimes a ptr and sometimes not
	TextHolder getMaterialName() {
		if (testValue == 0)
			return *this->materialNamePtr;
		else
			return this->materialName;
	}
};

class LevelRendererPlayer {
public:
	BUILD_ACCESS(this, MaterialPtr*, shadowBack, 0x238);
	BUILD_ACCESS(this, MaterialPtr*, shadowFront, 0x248);
	BUILD_ACCESS(this, MaterialPtr*, shadowOverlay, 0x258);
	BUILD_ACCESS(this, MaterialPtr*, stars, 0x268);
	BUILD_ACCESS(this, MaterialPtr*, skyplane, 0x278);
	BUILD_ACCESS(this, MaterialPtr*, sunMoon, 0x288);
	BUILD_ACCESS(this, MaterialPtr*, endSky, 0x298);
	BUILD_ACCESS(this, MaterialPtr*, clouds, 0x2A8);
	BUILD_ACCESS(this, MaterialPtr*, wireframe, 0x2B8);
	BUILD_ACCESS(this, MaterialPtr*, cubemap, 0x2C8);
	BUILD_ACCESS(this, Vec3, cameraPos, 0x514);
};

class LevelRenderer {
public:
	BUILD_ACCESS(this, LevelRendererPlayer*, levelRendererPlayer, 0x2F8);
	Vec3& getOrigin() {
		return levelRendererPlayer->cameraPos;
	}
};

class HitDetectSystem;

struct FontRepository_FontList_FontEntry {
public:
	Font* font;

private:
	void* sharedFontPtr;
};

struct FontRepository_FontList {
public:
	FontRepository_FontList_FontEntry fontEntries[9];
};

struct FontRepository {
private:
	uintptr_t* font_repository_vtable;  // 0x0000
	__int64 pad;                        // 0x0008
	void* ptrToSelf;                    // 0x0010
	void* ptrToSelfSharedPtr;           // 0x0018
public:
	FontRepository_FontList* fontList;  //0x0020
};

class MinecraftGame {
public:
	BUILD_ACCESS(this, FontRepository**, fontRepository, 0xEC8);
	BUILD_ACCESS(this, Font*, mcFont, 0xED8);
	BUILD_ACCESS(this, bool, canUseKeys, 0x130);

	Font* getTheGoodFontThankYou() {
		return (*fontRepository)->fontList->fontEntries[7].font;
	};

	Font* getTheRandomFontPlease() {
		return (*fontRepository)->fontList->fontEntries[4].font;
	};

	Font* getOldFont() {
		return (*fontRepository)->fontList->fontEntries[7].font;
	};

	Font* getTheBetterFontYes() {
		return (*fontRepository)->fontList->fontEntries[3].font;
	}

	Font* getMCFont() {
		return mcFont;
	}

	const bool canUseKeybinds() {
		return canUseKeys;
	};

	__int64 getServerEntries();
};

class GuiData {
private:
	char pad_0x0000[0x30];  //0x0000
public:
	union {
		struct {
			float widthReal;   //0x0030
			float heightReal;  //0x0034
		};
		Vec2 windowSizeReal;  //0x0030
	};

	float widthReal2;   //0x0038
	float heightReal2;  //0x003C
	union {
		struct {
			float widthGame;   //0x0040
			float heightGame;  //0x0044
		};
		Vec2 windowSize;  //0x0040
	};

	void displayClientMessageVA(const char* fmt, va_list lis);

	void displayClientMessageF(const char* fmt, ...);
	void displayClientMessageNoSendF(const char* fmt, ...);
	void displayClientMessage(std::string* a2);
};

struct PtrToGameSettings3 {
private:
	char pad_0x0000[0x18];  //0x0000
public:
	GameSettingsInput* settingsInput;
};

struct PtrToGameSettings2 {
private:
	char pad_0x0000[0x148];  //0x0000
public:
	PtrToGameSettings3* ptr;
};

struct PtrToGameSettings1 {
private:
	char pad_0x0000[0x20];  //0x0000
public:
	PtrToGameSettings2* ptr;
};

class MoveInputHandler;
class CameraManager;

class ItemInHandRenderer {
public:
	BUILD_ACCESS(this, MaterialPtr*, opaqueBlock, 0x1A8);
	BUILD_ACCESS(this, MaterialPtr*, opaqueBlockColor, 0x1B8);
	BUILD_ACCESS(this, MaterialPtr*, entityAlphatest, 0x1C8);
	BUILD_ACCESS(this, MaterialPtr*, itemInHand, 0x1D8);
	BUILD_ACCESS(this, MaterialPtr*, entityAlphablend, 0x1E8);
	BUILD_ACCESS(this, MaterialPtr*, entityAlphablendNoColor, 0x1F8);
	BUILD_ACCESS(this, MaterialPtr*, itemInHandEntityAlphatestColor, 0x208);
	BUILD_ACCESS(this, MaterialPtr*, itemInHandMulticolorTint, 0x218);
	BUILD_ACCESS(this, MaterialPtr*, entityGlint, 0x228);
	BUILD_ACCESS(this, MaterialPtr*, entityAlphatestGlint, 0x238);
	BUILD_ACCESS(this, MaterialPtr*, itemInHandGlint, 0x248);
	BUILD_ACCESS(this, MaterialPtr*, entityFlatColorLine, 0x258);
};

class ClientInstance {
private:
	char pad_0x0[0xC8];  // 0x0
public:
	MinecraftGame* minecraftGame;  // 0xC8
	Minecraft* minecraft;          // 0xD0
private:
	char pad_0xD8[0x8];  // 0xD8
public:
	LevelRenderer* levelRenderer;  // 0xE0
private:
	char pad_0xE8[0x8];  // 0xE8
public:
	LoopbackPacketSender* loopbackPacketSender;  // 0xF0
private:
	char pad_0xF8[0x18];  // 0xF8
public:
	PtrToGameSettings1* ptr;  // 0x110
private:
	char pad_0x118[0x8];  // 0x118
public:
	HitDetectSystem* hitDetectSystem;  // 0x120
private:
	char pad_0x128[0x3D8];  // 0x128
public:
	class ItemInHandRenderer* itemInHandRenderer;  // 0x500

	glmatrixf* getRefDef() {
		return reinterpret_cast<glmatrixf*>((uintptr_t)(this) + 0x300);
	};

	Vec2* getMousePos() {
		return reinterpret_cast<Vec2*>((uintptr_t)(this) + 0x468);
	}

	Vec2 getFov() {
		Vec2 fov;
		fov.x = *reinterpret_cast<float*>((uintptr_t)(this) + 0x6A0);
		fov.y = *reinterpret_cast<float*>((uintptr_t)(this) + 0x6B4);
		return fov;
	}

	Font* getFont() {
		using getFont_t = Font*(__fastcall*)(ClientInstance*);
		static getFont_t getFontFunc = reinterpret_cast<getFont_t>(FindSignature("48 89 5C 24 ? 57 48 83 EC 30 48 8B DA 48 8B 89 ? ? ? ? 48 8B 01 48 8D 54 24 ? 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 90 48 8B 10 48 85 D2 74 65 48 8B 48 08 48 85 C9 74 0B F0 FF 41 08 48 8B 10 48 8B 48 08 48 8B 3A 48 85 C9 74 05 E8 ? ? ? ? 48 8B D7 48 8B CB E8 ? ? ? ? 90 33 C0 48 89 44 24 ? 48 8B 4C 24 ? 48 89 44 24 ? 48 85 C9 74 14 E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 05 E8 ? ? ? ? 48 8B C3 48 8B 5C 24 ? 48 83 C4 30 5F C3 E8 ? ? ? ? 90 CC CC CC 48 83 EC 28"));
		return getFontFunc(this);
	}

	Font* getRuneFont() {
		using getRuneFont_t = Font*(__fastcall*)(ClientInstance*);
		static getRuneFont_t getRuneFontFunc = reinterpret_cast<getRuneFont_t>(FindSignature("48 89 5C 24 ? 57 48 83 EC 30 48 8B DA 48 8B 89 ? ? ? ? 48 8B 01 48 8D 54 24 ? 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 90 48 8B 10 48 85 D2 74 65 48 8B 48 08 48 85 C9 74 0B F0 FF 41 08 48 8B 10 48 8B 48 08 48 8B 3A 48 85 C9 74 05 E8 ? ? ? ? 48 8B D7 48 8B CB E8 ? ? ? ? 90 33 C0 48 89 44 24 ? 48 8B 4C 24 ? 48 89 44 24 ? 48 85 C9 74 14 E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 05 E8 ? ? ? ? 48 8B C3 48 8B 5C 24 ? 48 83 C4 30 5F C3 E8 ? ? ? ? 90 CC CC CC 48 89 5C 24 ?"));
		return getRuneFontFunc(this);
	}

	Font* getUnicodeFont() {
		using getUnicodeFont_t = Font*(__fastcall*)(ClientInstance*);
		static getUnicodeFont_t getUnicodeFontFunc = reinterpret_cast<getUnicodeFont_t>(FindSignature("48 89 5C 24 ? 57 48 83 EC 30 48 8B DA 48 8B 89 ? ? ? ? 48 8B 01 48 8D 54 24 ? 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 90 48 8B 10 48 85 D2 74 65 48 8B 48 08 48 85 C9 74 0B F0 FF 41 08 48 8B 10 48 8B 48 08 48 8B 3A 48 85 C9 74 05 E8 ? ? ? ? 48 8B D7 48 8B CB E8 ? ? ? ? 90 33 C0 48 89 44 24 ? 48 8B 4C 24 ? 48 89 44 24 ? 48 85 C9 74 14 E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 05 E8 ? ? ? ? 48 8B C3 48 8B 5C 24 ? 48 83 C4 30 5F C3 E8 ? ? ? ? 90 CC CC CC 40 53"));
		return getUnicodeFontFunc(this);
	}

	Font* _getFont() {
		return this->getFont();
	}

	Font* _getRuneFont() {
		return this->getRuneFont();
	}

	Font* _getUnicodeFont() {
		return this->getUnicodeFont();
	}

	void grabMouse() {
		return Utils::CallVFunc<304, void>(this);
	}

	void releaseMouse() {
		return Utils::CallVFunc<305, void>(this);
	}

	GuiData* getGuiData() {
		return (GuiData*)*reinterpret_cast<__int64*>(reinterpret_cast<GuiData*>(reinterpret_cast<__int64>(this) + 0x510));
	};

	BlockTessellator* getBlockTesselator() {
		return (BlockTessellator*)*reinterpret_cast<__int64*>(reinterpret_cast<BlockTessellator*>(reinterpret_cast<__int64>(this) + 0x4D8));
	};

	class LocalPlayer* getCILocalPlayer() {
		return Utils::CallVFunc<27, LocalPlayer*>(this);
	}

	MoveInputHandler* getMoveTurnInput() {
		uint32_t id = this->getCILocalPlayer()->entityIdentifier;
		LocalPlayer* player = this->getCILocalPlayer();

		using MoveInputComponent_try_get = MoveInputHandler*(__cdecl *)(void *, EntityId *);
		static MoveInputComponent_try_get MoveInputComponent_try_getFunc = reinterpret_cast<MoveInputComponent_try_get>(FindSignature("40 53 48 83 EC 20 48 8B DA BA 2E CD 8B 46"));
		auto registryBase = *reinterpret_cast<void**>(player->ctx.registry);
		return MoveInputComponent_try_getFunc(registryBase, &player->ctx.id);
	}

	inline GameSettingsInput* getGameSettingsInput() { return this->ptr->ptr->ptr->settingsInput; };
};