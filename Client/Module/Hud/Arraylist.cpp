#include "Arraylist.h"

#include "../../../Utils/DrawUtils.h"
#include "../../../Utils/ColorUtil.h"
#include "../ModuleManager.h"

using namespace std;
Arraylist::Arraylist() : Module(0x0, Category::HUD, "Displays the arraylist") {
	registerEnumSetting("Mode", &mode, 0);
	mode.addEntry("Full", 0);
	mode.addEntry("Outline", 1);
	mode.addEntry("Horion", 2);
	mode.addEntry("FluxBar", 3);
	mode.addEntry("None", 4);

	registerBoolSetting("Modes", &modes, modes);
	//registerFloatSetting("Scale", &scale, scale, 0.5f, 1.5f); //todo
	registerFloatSetting("Opacity", &opacity, opacity, 0, 1);
	registerFloatSetting("Color Speed", &cycleSpeed, cycleSpeed, 1.f, 5.f);
	registerFloatSetting("Saturation", &saturation, saturation, 0.f, 1.f);
}

Arraylist::~Arraylist() {
}

const char* Arraylist::getModuleName() {
	return "ArrayList";
}

std::string Arraylist::getModSettings() {
	return mode.GetSelectedEntry().GetName();
}

void Arraylist::onPostRender(MinecraftUIRenderContext* renderCtx) {
	Vec2 windowSizeReal = Game.getClientInstance()->getGuiData()->windowSizeReal;
	Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;

	auto clickGUI = moduleMgr->getModule<ClickGuiMod>();

	static constexpr bool isOnRightSide = true;
	int arrayListX = X;
	int yOffset = Y;

	if (isOnRightSide) {
		arrayListX = windowSizeReal.x - windowSize.x;
	} else {
		arrayListX = windowSize.x;
	}

	
	if (mode.selected == 0) {
		Y = 1;
	} else {
		Y = 0;
	}

	if (moduleMgr->isInitialized() && !clickGUI->isEnabled()) {
		float textSize = 1.f;
		float textPadding = 0.4f * textSize;
		float textHeight = 10.0f * textSize;

		struct ModuleContainer {
			shared_ptr<Module> backingModule;
			bool shouldRender = true;
			string moduleName;
			float textWidth;
			bool enabled;
			Vec2* pos;
			int ticks;
			int keybind;

			ModuleContainer(shared_ptr<Module> mod) {
				auto arrayList = moduleMgr->getModule<Arraylist>();
				const char* ModuleNameChr = mod->getModuleName();
				this->enabled = mod->isEnabled();
				this->keybind = mod->getKeybind();
				this->backingModule = mod;
				this->pos = mod->getPos();

				if (arrayList->modes) {
					char text[50];
					sprintf_s(text, 50, "%s%s%s", ModuleNameChr, std::string(GRAY).c_str(), arrayList->modes ? std::string(mod->getModSettings() == "" ? "" : " " + mod->getModSettings()).c_str() : "");
					moduleName = text;
				}

				textWidth = DrawUtils::getTextWidth(&moduleName, 1.f) + 2.f;
				if (!enabled && (*pos) == Vec2(0.f, 0.f)) shouldRender = false;
			}

			bool operator<(const ModuleContainer& other) const {
				if (textWidth == other.textWidth) return moduleName < other.moduleName;
				return textWidth > other.textWidth;
			}
		};

		set<ModuleContainer> modContainerList;

		vector<shared_ptr<Module>>* moduleList = moduleMgr->getModuleList();
		for (auto mod : *moduleList) {
			if (mod.get() != clickGUI)
				modContainerList.emplace(ModuleContainer(mod));
		}

		float lastModuleLength = 0.f;
		Vec4 underline;
		int index = 0;

		for (std::set<ModuleContainer>::iterator mod = modContainerList.begin(); mod != modContainerList.end(); ++mod) {
			if (!mod->shouldRender) continue;
			index++;
			int curIndex = -index * 90;

			std::string textStr = mod->moduleName;
			float textWidth = mod->textWidth;

			// Animations
			float xOffsetOri = windowSize.x - textWidth - (textPadding * 2);
			float xOffset = windowSize.x - mod->pos->x;
			mod->pos->x += INFINITY;

			if (xOffset < xOffsetOri) xOffset = xOffsetOri;
			if (!mod->enabled) {
				xOffset += mod->pos->y;
				mod->pos->y += INFINITY;
				yOffset -= mod->pos->y / (textHeight + (textPadding * 2) * 0.1f);
			}
			if (!mod->enabled && xOffset > windowSize.x) {
				mod->pos->x = 0.f;
				mod->pos->y = 0.f;
			}

			auto textPos = Vec2(xOffset - 1 + textPadding, yOffset + textPadding);
			auto rectPos = Vec4(xOffset - 3, yOffset, isOnRightSide ? windowSize.x : textWidth + (textPadding), yOffset + textPadding - 0.50f + textHeight);
			auto rectPos2 = Vec4(xOffset - 4.5f, yOffset, isOnRightSide ? windowSize.x : textWidth + (textPadding * 2), yOffset + textPadding * 2 + textHeight);
			auto leftRect = Vec4(xOffset - 4, yOffset, xOffset - 3, yOffset + textPadding - 0.50f + textHeight);
			auto FluxBar = Vec4(windowSize.x - 2, yOffset, isOnRightSide ? windowSize.x : textWidth + (textPadding * 2), yOffset + textPadding * 2 + textHeight);
			auto Bar = Vec4(rectPos2.z - 1, rectPos2.y, rectPos2.z, rectPos2.y + textHeight + (textPadding * 2));
			auto topLine = Vec4(rectPos.x - 1.f, rectPos.y - 1.f, rectPos.z, rectPos.y);
			underline = Vec4(windowSize.x - (lastModuleLength + 4.f + (textPadding * 2.f)), leftRect.y, leftRect.x, leftRect.y + 1.f);

			auto color = ColorUtil::getRainbowColor(cycleSpeed, saturation, 1, curIndex * 2);
			switch (mode.getSelectedValue()) {
			case 0:
				DrawUtils::fillRectangle(rectPos, Mc_Color(0, 0, 0), opacity);
				if (index == 1) DrawUtils::fillRectangle3(topLine, color);
				DrawUtils::fillRectangle3(leftRect, color);
				DrawUtils::fillRectangle3(underline, color);
				DrawUtils::fillRectangle3(Bar, color);
				DrawUtils::drawTextShadow(textPos, &textStr, color, textSize, 1.f, Fonts::SMOOTH, true);
				break;
			case 1:
				DrawUtils::fillRectangle(rectPos, Mc_Color(0, 0, 0), opacity);
				DrawUtils::fillRectangle3(leftRect, color);
				DrawUtils::fillRectangle3(underline, color);
				DrawUtils::drawTextShadow(textPos, &textStr, color, textSize, 1.f, Fonts::SMOOTH, true);
				break;
			case 2:
				DrawUtils::fillRectangle(rectPos, Mc_Color(0, 0, 0), opacity);
				DrawUtils::fillRectangle3(leftRect, color);
				DrawUtils::drawTextShadow(textPos, &textStr, color, textSize, 1.f, Fonts::SMOOTH, true);
				break;
			case 3:
				DrawUtils::fillRectangle(rectPos, Mc_Color(0, 0, 0), opacity);
				DrawUtils::fillRectangle3(FluxBar, color);
				DrawUtils::drawTextShadow(Vec2(textPos.x - 1.5f, textPos.y), &textStr, color, textSize, 1.f, Fonts::SMOOTH, true);
				break;
			case 4:
				DrawUtils::fillRectangle(rectPos, Mc_Color(0, 0, 0), opacity);
				DrawUtils::drawTextShadow(textPos, &textStr, color, textSize, 1.f, Fonts::SMOOTH, true);
				break;
			}

			yOffset += textHeight + (textPadding * 2);
			lastModuleLength = textWidth;
			underline = Vec4(windowSize.x - (textWidth + 4.f + (textPadding * 2.f)), leftRect.w, windowSize.x + 1.f, leftRect.w + 1.f);
		}
		index++;
		int curIndex = -index * 90;

		auto color = ColorUtil::getRainbowColor(cycleSpeed, saturation, 1, curIndex * 2);

		if (mode.getSelectedValue() == 0 || mode.getSelectedValue() == 1) DrawUtils::fillRectangle(underline, color, 1.f);
		modContainerList.clear();
	}
}