#include "Arraylist.h"

#include "../../../Utils/DrawUtils.h"
#include "../../../Utils/ColorUtil.h"
#include "../ModuleManager.h"
#include "../Module.h"

using namespace std;
Arraylist::Arraylist() : Module(0x0, Category::HUD, "Displays the arraylist") {
	registerFloatSetting("Padding", &padding, padding, 0.0f, 1.0f, "Padding: Adjust text padding from 0 to 1");
	registerFloatSetting("Scale", &scale, scale, 0.5f, 2.0f, "Scale: Adjust text scale from 0.5 to 2.0");

	registerEnumSetting("Mode", &mode, 0, "Changes The Arraylist Type");
	mode.addEntry("Full", 0);
	mode.addEntry("Outline", 1);
	mode.addEntry("Horion", 2);
	mode.addEntry("FluxBar", 3);
	mode.addEntry("None", 4);

	registerBoolSetting("Modes", &modes, modes, "Toggles The Module And Info (Reach 7.0)");
	registerFloatSetting("Opacity", &opacity, opacity, 0, 1, "Opacity: Adjust transparency from invisible (0) to solid (1)");
	registerFloatSetting("Color Speed", &cycleSpeed, cycleSpeed, 1.f, 5.f, "Color Speed: Set the speed of color change (1 to 5)");
	registerFloatSetting("Saturation", &saturation, saturation, 0.f, 1.f, "Saturation: Control color vividness (0 to 1).");
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

	int index = 0;
	index++;
	int curIndex = -index * 90;
	auto color = ColorUtil::getRainbowColor(cycleSpeed, saturation, 1, curIndex * 2);

	static constexpr bool isOnRightSide = true;
	int arrayListX = X;
	int yOffset = Y;

	if (isOnRightSide) {
		arrayListX = windowSizeReal.x - windowSize.x;
	} else {
		arrayListX = windowSize.x;
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

			ModuleContainer(shared_ptr<Module> mod) {
				auto arrayList = moduleMgr->getModule<Arraylist>();
				const char* ModuleNameChr = mod->getModuleName();
				this->enabled = mod->isEnabled();
				this->backingModule = mod;
				this->pos = mod->getPos();

				if (arrayList->modes) {
					char text[50];
					sprintf_s(text, 50, "%s%s%s", ModuleNameChr, std::string(GRAY).c_str(), arrayList->modes ? std::string(mod->getModSettings() == "" ? "" : " " + mod->getModSettings()).c_str() : "");
					moduleName = text;

					textWidth = DrawUtils::getTextWidth(&moduleName, 1.f) + 2.f;
					if (!enabled && (*pos) == Vec2(0.f, 0.f)) shouldRender = false;
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

		if (mode.selected == 0) {
			Y = 1;
		} else {
			Y = 0;
		}

		vector<shared_ptr<Module>>* moduleList = moduleMgr->getModuleList();
		for (auto mod : *moduleList) {
			if (mod.get() != clickGUI)
				modContainerList.emplace(ModuleContainer(mod));
		}

		float lastModuleLength = 0.f;
		Vec4 underline;

		for (std::set<ModuleContainer>::iterator mod = modContainerList.begin(); mod != modContainerList.end(); ++mod) {
			if (!mod->shouldRender) continue;

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

			switch (mode.getSelectedValue()) {
			case 0:
				DrawUtils::drawTextShadow(textPos, &textStr, color, textSize, 1.f, Fonts::SMOOTH, true);
				DrawUtils::fillRectangle(rectPos, Mc_Color(0, 0, 0), opacity);
				if (index == 1) DrawUtils::fillRectangle3(topLine, color);
				DrawUtils::fillRectangle3(leftRect, color);
				DrawUtils::fillRectangle3(underline, color);
				DrawUtils::fillRectangle3(Bar, color);
				break;
			case 1:
				DrawUtils::drawTextShadow(textPos, &textStr, color, textSize, 1.f, Fonts::SMOOTH, true);
				DrawUtils::fillRectangle(rectPos, Mc_Color(0, 0, 0), opacity);
				DrawUtils::fillRectangle3(leftRect, color);
				DrawUtils::fillRectangle3(underline, color);
				break;
			case 2:
				DrawUtils::drawTextShadow(textPos, &textStr, color, textSize, 1.f, Fonts::SMOOTH, true);
				DrawUtils::fillRectangle(rectPos, Mc_Color(0, 0, 0), opacity);
				DrawUtils::fillRectangle3(leftRect, color);
				break;
			case 3:
				DrawUtils::drawTextShadow(textPos, &textStr, color, textSize, 1.f, Fonts::SMOOTH, true);
				DrawUtils::fillRectangle(rectPos, Mc_Color(0, 0, 0), opacity);
				DrawUtils::fillRectangle3(Bar, color);
				break;
			case 4:
				DrawUtils::drawTextShadow(textPos, &textStr, color, textSize, 1.f, Fonts::SMOOTH, true);
				DrawUtils::fillRectangle(rectPos, Mc_Color(0, 0, 0), opacity);
				break;
			}

			yOffset += textHeight + (textPadding * 2);
			lastModuleLength = textWidth;
			underline = Vec4(windowSize.x - (textWidth + 4.f + (textPadding * 2.f)), leftRect.w, windowSize.x + 1.f, leftRect.w + 1.f);
		}

		if (mode.getSelectedValue() == 0 || mode.getSelectedValue() == 1) DrawUtils::fillRectangle(underline, color, 1.f);
		modContainerList.clear();
	}
}