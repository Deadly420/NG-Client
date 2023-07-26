#include "ClickGui.h"

#include "../../Utils/Logger.h"
#include <Windows.h>

bool resetStartPos = true;
bool initialised = false;
int scrollingDirection = 0;

struct SavedWindowSettings {
	Vec2 pos = {-1, -1};
	bool isExtended = true;
	const char* name = "";
};

std::map<unsigned int, std::shared_ptr<ClickWindow>> windowMap;
std::map<unsigned int, SavedWindowSettings> savedWindowSettings;

bool isDragging = false;
unsigned int draggedWindow = -1;
Vec2 dragStart = Vec2();

unsigned int focusedElement = -1;
bool isFocused = false;
static constexpr float textPaddingX = 2.4f;
static constexpr float textPaddingY = 1.4f;

static constexpr float textSize = 0.75f;
static constexpr float textHeight = textSize * 10.0f;
static constexpr float categoryMargin = 0.5f;
static constexpr float paddingRight = 13.5f;
static constexpr float crossSize = textHeight / 2.f;
static constexpr float crossWidth = 0.3f;
static constexpr float ArrowSize = textHeight / 5.f;
static constexpr float ArrowWidth = 0.3f;
static constexpr float backgroundAlpha = 0.40f;
static const Mc_Color whiteColor = Mc_Color(255, 255, 255);
static const Mc_Color moduleColor = Mc_Color(0, 0, 0); // background

static const Mc_Color enabledModuleColor = moduleColor.lerp(whiteColor, 0.04f);

float currentYOffset = 0;
float currentXOffset = 0;

int timesRendered = 0;

void ClickGui::getModuleListByCategory(Category category, std::vector<std::shared_ptr<Module>>* modList) {
	auto lock = moduleMgr->lockModuleList();
	std::vector<std::shared_ptr<Module>>* moduleList = moduleMgr->getModuleList();

	for (auto& it : *moduleList) {
		if (it->getCategory() == category)
			modList->push_back(it);
	}
}

std::shared_ptr<ClickWindow> ClickGui::getWindow(const char* name) {
	unsigned int id = Utils::getCrcHash(name);

	auto search = windowMap.find(id);
	if (search != windowMap.end()) {  // Window exists already
		return search->second;
	} else {  // Create window
		// TODO: restore settings for position etc
		std::shared_ptr<ClickWindow> newWindow = std::make_shared<ClickWindow>();
		newWindow->name = name;

		auto savedSearch = savedWindowSettings.find(id);
		if(savedSearch != savedWindowSettings.end()){ // Use values from config
			newWindow->isExtended = savedSearch->second.isExtended;
			if(savedSearch->second.pos.x > 0)
				newWindow->pos = savedSearch->second.pos;
		}

		windowMap.insert(std::make_pair(id, newWindow));
		return newWindow;
	}
}

std::shared_ptr<ClickModule> ClickGui::getClickModule(std::shared_ptr<ClickWindow> window, const char* name) {
	unsigned int id = Utils::getCrcHash(name);

	auto search = window->moduleMap.find(id);
	if (search != window->moduleMap.end()) {  // Window exists already
		return search->second;
	} else {  // Create window
		// TODO: restore settings for position etc
		std::shared_ptr<ClickModule> newModule = std::make_shared<ClickModule>();

		window->moduleMap.insert(std::make_pair(id, newModule));
		return newModule;
	}
}

void ClickGui::renderLabel(const char* text) {
}

void ClickGui::renderTooltip(std::string* text) {
	Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
	Vec2 currentTooltipPos = Vec2(5.f, windowSize.y - 15.f);
	float textWidth = DrawUtils::getTextWidth(text, textSize);
	Vec2 textPos = Vec2(
		currentTooltipPos.x + textPaddingX,
		currentTooltipPos.y);
	Vec4 rectPos = Vec4(
		currentTooltipPos.x - 2.f,
		currentTooltipPos.y - 2.f,
		currentTooltipPos.x + (textPaddingX * 2) + textWidth + 2.f,
		currentTooltipPos.y + textHeight + 2.f);

	Vec4 rectPosbottom = Vec4(
		currentTooltipPos.x - 2.f,
		currentTooltipPos.y + 10.f,
		currentTooltipPos.x + (textPaddingX * 2) + textWidth + 2.f,
		currentTooltipPos.y + textHeight + 2.f);

	DrawUtils::fillRectangle(rectPos, moduleColor, backgroundAlpha);		  // tooltips
	DrawUtils::drawBoxBottom(rectPosbottom, Mc_Color(184, 0, 255), 1, 0.5);  // tooltips
	DrawUtils::drawText(textPos, text, Mc_Color(0, 246, 255), textSize);    // tooltips
}

void ClickGui::renderCategory(Category category) {
	const char* categoryName = ClickGui::catToName(category);

	const std::shared_ptr<ClickWindow> ourWindow = getWindow(categoryName);

	// Reset Windows to pre-set positions to avoid confusion
		if (resetStartPos) {
			float yot = Game.getGuiData()->windowSize.x;
			ourWindow->pos.y = 4;
			switch (category) {
			case Category::COMBAT:
				ourWindow->pos.x = 6;
				ourWindow->pos.y = 1;
				break;
			case Category::RENDER:
				ourWindow->pos.x = yot / 11.f;
				ourWindow->pos.y = 1;
				break;
			case Category::MOVEMENT:
				ourWindow->pos.x = yot / 11.f * 2.f;
				ourWindow->pos.y = 1; 
				break;
			case Category::PLAYER:
				ourWindow->pos.x = yot / 11.f * 3.f;
				ourWindow->pos.y = 1;
				break;
			case Category::ENTITY:
				ourWindow->pos.x = yot / 11.f * 4.f;
				ourWindow->pos.y = 1;
				break;
			case Category::MISC:
				ourWindow->pos.x = yot / 11.f * 5.08f;
				ourWindow->pos.y = 1;
				break;
			case Category::WORLD:
				ourWindow->pos.x = yot / 11.f * 3.f;
				ourWindow->pos.y = 148.f;
				break;
			case Category::HUD:
				ourWindow->pos.x = yot / 11.f * 4.f;
				ourWindow->pos.y = 78.f;
				break;
			default:
				break;
		}
	}

	const float xOffset = ourWindow->pos.x;
	const float yOffset = ourWindow->pos.y;
	Vec2* windowSize = &ourWindow->size;
	currentXOffset = xOffset;
	currentYOffset = yOffset;

	// Get All Modules in our category
	std::vector<std::shared_ptr<Module>> moduleList;
	getModuleListByCategory(category, &moduleList);

	// Get max width of all text
	{
		for (auto& it : moduleList) {
			std::string label = it->getModuleName();
			windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&label, textSize, Fonts::SMOOTH));
		}
	}

	const float xEnd = currentXOffset + windowSize->x + paddingRight;

	Vec2 mousePos = *Game.getClientInstance()->getMousePos();

	// Convert mousePos to visual Pos
	{
		Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;
		Vec2 windowSizeReal = Game.getClientInstance()->getGuiData()->windowSizeReal;

		mousePos = mousePos.div(windowSizeReal);
		mousePos = mousePos.mul(windowSize);
	}

	float categoryHeaderYOffset = currentYOffset;

	if (ourWindow->isInAnimation) {
		if (ourWindow->isExtended) {
			ourWindow->animation *= 0.90f;
			if (ourWindow->animation < 0.001f) {
				ourWindow->yOffset = 0;  // reset scroll
				ourWindow->isInAnimation = false;
			}

		} else {
			ourWindow->animation = 1 - ((1 - ourWindow->animation) * 0.93f);
			if (1 - ourWindow->animation < 0.001f)
				ourWindow->isInAnimation = false;
		}
	}

	currentYOffset += textHeight + (textPaddingY * 2);
	// Loop through Modules to display em
	if (ourWindow->isExtended || ourWindow->isInAnimation) {
		if (ourWindow->isInAnimation) {
			currentYOffset -= ourWindow->animation * moduleList.size() * (textHeight + (textPaddingY * 2));
		}

		bool overflowing = false;
		const float cutoffHeight = roundf(Game.getGuiData()->heightGame * 0.75f) + 0.5f /*fix flickering related to rounding errors*/;
		int moduleIndex = 0;
		for (auto& mod : moduleList) {
			moduleIndex++;
			if (moduleIndex < ourWindow->yOffset)
				continue;
			float probableYOffset = (moduleIndex - ourWindow->yOffset) * (textHeight + (textPaddingY * 2));
			
			if (ourWindow->isInAnimation) { // Estimate, we don't know about module settings yet
				if (probableYOffset > cutoffHeight) {
					overflowing = true;
					break;
				}
			}else if ((currentYOffset - ourWindow->pos.y) > cutoffHeight || currentYOffset > Game.getGuiData()->heightGame - 5) {
				overflowing = true;
				break;
			}

			std::string textStr = mod->getModuleName();

			Vec2 textPos = Vec2(
				currentXOffset + textPaddingX,
				currentYOffset + textPaddingY);
			Vec4 rectPos = Vec4(
				currentXOffset,
				currentYOffset,
				xEnd,
				currentYOffset + textHeight + (textPaddingY * 2));

			bool allowRender = currentYOffset >= categoryHeaderYOffset;

			// Background
			if (allowRender) {
				if (!ourWindow->isInAnimation && !isDragging && rectPos.contains(&mousePos)) {  // Is the Mouse hovering above us?
					DrawUtils::fillRectangle(rectPos, Mc_Color(50, 50, 50), backgroundAlpha);
					std::string tooltip = mod->getTooltip();
					static auto clickGuiMod = moduleMgr->getModule<ClickGuiMod>();
					if (clickGuiMod->showTooltips && !tooltip.empty())
						renderTooltip(&tooltip);
					if (DrawUtils::shouldToggleLeftClick && !ourWindow->isInAnimation) {  // Are we being clicked?
						mod->toggle();
						DrawUtils::shouldToggleLeftClick = false;
					}
				} else {
					DrawUtils::fillRectangle(rectPos, mod->isEnabled() ? Mc_Color(30, 30, 30) : Mc_Color(18, 18, 18), backgroundAlpha);
				
				}
			}

			// Text
			if (allowRender)
				DrawUtils::drawText(textPos, &textStr, mod->isEnabled() ? Mc_Color(0, 246, 255) : whiteColor, textSize);

			// Settings
			{
				std::vector<SettingEntry*>* settings = mod->getSettings();
				auto clickguiMod = moduleMgr->getModule<ClickGuiMod>();
				if (settings->size() > 2 && allowRender) {
					std::shared_ptr<ClickModule> clickMod = getClickModule(ourWindow, mod->getRawModuleName());
					if (rectPos.contains(&mousePos) && DrawUtils::shouldToggleRightClick && !ourWindow->isInAnimation) {
						DrawUtils::shouldToggleRightClick = false;
						clickMod->isExtended = !clickMod->isExtended;
					}
					if (clickguiMod->mode.selected == 0) {
						if (!clickMod->isExtended)
							GuiUtils::drawDownArrow(Vec2(currentXOffset + windowSize->x + paddingRight - 5.5f, currentYOffset + textPaddingY + (textHeight / 3)), whiteColor, ArrowWidth, ArrowSize);
						else
							GuiUtils::drawUpArrow(Vec2(currentXOffset + windowSize->x + paddingRight - 5.5f, currentYOffset + textPaddingY + (textHeight / 1.5)), whiteColor, ArrowWidth, ArrowSize);
					} else {
						GuiUtils::drawCrossLine(Vec2(currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f, currentYOffset + textPaddingY + (textHeight / 2)), whiteColor, crossWidth, crossSize, !clickMod->isExtended);
					}

					currentYOffset += textHeight + (textPaddingY * 2);

					if (clickMod->isExtended) {
						float startYOffset = currentYOffset;
						for (auto setting : *settings) {
								if (strcmp(setting->name, "enabled") == 0 || strcmp(setting->name, "keybind") == 0)
								continue;

							Vec2 textPos = Vec2(
								currentXOffset + textPaddingX + 5,
								currentYOffset + textPaddingY);

							// Incomplete, because we don't know the endY yet
							Vec4 rectPos = Vec4(
								currentXOffset,
								currentYOffset,
								xEnd,
								0);

							if ((currentYOffset - ourWindow->pos.y) > cutoffHeight) {
								overflowing = true;
								break;
							}

							switch (setting->valueType) {
							case ValueType::BOOL: {
								rectPos.w = currentYOffset + textHeight + (textPaddingY * 2);
								// Background of bool setting
								DrawUtils::fillRectangle(rectPos, Mc_Color(18, 18, 18), backgroundAlpha);
								Vec4 selectableSurface = Vec4(
									textPos.x + textPaddingX,
									textPos.y + textPaddingY,
									xEnd - textPaddingX,
									textPos.y + textHeight - textPaddingY);

								bool isFocused = selectableSurface.contains(&mousePos);
								// Logic
								{
									if (isFocused && DrawUtils::shouldToggleLeftClick && !ourWindow->isInAnimation) {
										DrawUtils::shouldToggleLeftClick = false;
										setting->value->_bool = !setting->value->_bool;
									}
								}
								// Checkbox
								{
									float boxHeight = textHeight - textPaddingY / 0.90;
									Vec4 boxPos = Vec4(
										textPos.x + textPaddingX,
										textPos.y + textPaddingY,
										textPos.x + textPaddingX + boxHeight,
										textPos.y + textPaddingY + boxHeight);

									DrawUtils::drawRectangle(boxPos, Mc_Color(255, 255, 255), isFocused ? 1 : 0.8f, 0.5f);

									if (setting->value->_bool) {
										DrawUtils::setColor(255, 255, 255, 1);
										boxPos.x += 1;
										boxPos.y += 1;
										boxPos.z -= 1;
										boxPos.w -= 1;

										DrawUtils::fillRectangle(boxPos, Mc_Color(255, 255, 255), isFocused ? 1 : 0.8f);
									}
								}
								textPos.x += textHeight + (textPaddingX * 1.50);
								// Text
								{
									// Convert first letter to uppercase for more friendlieness
									char name[0x21];
									sprintf_s(name, 0x21, "%s", setting->name);
									if (name[0] != 0)
										name[0] = toupper(name[0]);

									std::string elTexto = name;
									windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 10 /* because we add 10 to text padding + checkbox*/);
									DrawUtils::drawText(textPos, &elTexto, isFocused ? Mc_Color(255, 255, 255) : Mc_Color(0.8f, 0.8f, 0.8f), textSize);
									currentYOffset += textHeight + (textPaddingY * 2);
								}
								break;
							}
							case ValueType::ENUM: {
								// Text and background
								{
									EnumEntry& i = ((SettingEnum*)setting->extraData)->GetSelectedEntry();
									char str[0x21];
									sprintf_s(str, 0x21, " %s", i.GetName().c_str());
									if (str[0] != 0) str[0] = toupper(str[0]);
									std::string text = str;

									char name[0x22];
									sprintf_s(name, "%s:", setting->name);
									// Convert first letter to uppercase for more friendlieness
									if (name[0] != 0)
										name[0] = toupper(name[0]);

									std::string elTexto = name + text;
									rectPos.w = currentYOffset + textHeight + (textPaddingY * 2);
									windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 8 /* because we add 5 to text padding*/ + crossSize);
									// Background of enum setting

									if (rectPos.contains(&mousePos)) {
										DrawUtils::fillRectangle(rectPos, Mc_Color(50, 50, 50), backgroundAlpha);
										if (DrawUtils::shouldToggleRightClick && !ourWindow->isInAnimation) {
											DrawUtils::shouldToggleRightClick = false;
											setting->minValue->_bool = !setting->minValue->_bool;
										}
									} else
										DrawUtils::fillRectangle(rectPos, Mc_Color(18, 18, 18), backgroundAlpha);

									DrawUtils::drawText(textPos, &elTexto, whiteColor, textSize);

									currentYOffset += textHeight + (textPaddingY * 2);
								}
								if (setting->minValue->_bool) {
									int e = 0;
									auto enumData = reinterpret_cast<SettingEnum*>(setting->extraData);
									for (auto it = enumData->Entrys.begin();
										 it != enumData->Entrys.end(); it++, e++) {
										if ((currentYOffset - ourWindow->pos.y) > cutoffHeight) {
											overflowing = true;
											break;
										}
										bool isEven = e % 2 == 0;
										rectPos.y = currentYOffset;
										rectPos.w = currentYOffset + textHeight + (textPaddingY * 2);
										EnumEntry i = *it._Ptr;
										char name[0x21];
										sprintf_s(name, 0x21, "   %s", i.GetName().c_str());
										// Convert first letter to uppercase for more friendlieness
										if (name[0] != 0)
											name[0] = toupper(name[0]);
										std::string elTexto = name;
										windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(
																				&elTexto, textSize) +
																				5);  // because we add 5 to text padding
										textPos.y = currentYOffset + textPaddingY;
										Vec4 selectableSurface = Vec4(
											textPos.x,
											rectPos.y,
											xEnd,
											rectPos.w);
										Mc_Color col;
										if (setting->value->_int == e || (selectableSurface.contains(&mousePos) && !ourWindow->isInAnimation))
											col = Mc_Color(50, 50, 50);
										else
											col = Mc_Color(18, 18, 18);
										// Background of individual enum
										DrawUtils::fillRectangle(rectPos, Mc_Color(18, 18, 18), backgroundAlpha);
										DrawUtils::fillRectangle(selectableSurface, col, backgroundAlpha);
										DrawUtils::drawText(textPos, &elTexto, whiteColor);
										// logic
										if (selectableSurface.contains(&mousePos) &&
											DrawUtils::shouldToggleLeftClick && !ourWindow->isInAnimation) {
											DrawUtils::shouldToggleLeftClick = false;
											setting->value->_int = e;
										}
										currentYOffset += textHeight + (textPaddingY * 2);
									}
								}
								break;
							}
							case ValueType::FLOAT: {
								// Text and background
								{
									char str[10];
									sprintf_s(str, 10, "%.2f", setting->value->_float);
									std::string text = str;

									char name[0x22];
									sprintf_s(name, "%s: ", setting->name);
									if (name[0] != 0)
										name[0] = toupper(name[0]);
									std::string elTexto = name + text;

									windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 5 /* because we add 5 to text padding*/);
									DrawUtils::drawText(textPos, &elTexto, whiteColor, textSize);
									currentYOffset += textPaddingY + textHeight;
									rectPos.w = currentYOffset;
									DrawUtils::fillRectangle(rectPos, Mc_Color(18, 18, 18), backgroundAlpha);
								}
								if ((currentYOffset - ourWindow->pos.y) > cutoffHeight) {
									overflowing = true;
									break;
								}
								// Slider
								{
									Vec4 rect = Vec4(
										currentXOffset + textPaddingX + 5,
										currentYOffset + textPaddingY + 1,
										xEnd - textPaddingX,
										currentYOffset - textPaddingY + textHeight);

									// Visuals & Logic
									{
										rectPos.y = currentYOffset;
										rectPos.w += textHeight + (textPaddingY * 2);
										// Background
										const bool areWeFocused = rect.contains(&mousePos);

										DrawUtils::fillRectangle(rectPos, Mc_Color(18, 18, 18), backgroundAlpha);  // Background
										DrawUtils::drawRectangle(rect, whiteColor, 1.f, backgroundAlpha);          // Slider background

										const float minValue = setting->minValue->_float;
										const float maxValue = setting->maxValue->_float - minValue;
										float value = (float) fmax(0, setting->value->_float - minValue);  // Value is now always > 0 && < maxValue
										if (value > maxValue)
											value = maxValue;
										value /= maxValue;  // Value is now in range 0 - 1
										const float endXlol = (xEnd - textPaddingX) - (currentXOffset + textPaddingX + 5);
										value *= endXlol;  // Value is now pixel diff between start of bar and end of progress

										// Draw Progress
										{
											rect.z = rect.x + value;
											DrawUtils::fillRectangle(rect, Mc_Color(50, 50, 50), (areWeFocused || setting->isDragging) ? 1.f : 0.8f);
										}

										// Drag Logic
										{
											if (setting->isDragging) {
												if (DrawUtils::isLeftClickDown && !DrawUtils::isRightClickDown)
													value = mousePos.x - rect.x;
												else
													setting->isDragging = false;
											} else if (areWeFocused && DrawUtils::shouldToggleLeftClick && !ourWindow->isInAnimation) {
												DrawUtils::shouldToggleLeftClick = false;
												setting->isDragging = true;
											}
										}

										// Save Value
										{
											value /= endXlol;  // Now in range 0 - 1
											value *= maxValue;
											value += minValue;

											setting->value->_float = value;
											setting->makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt();
										}
									}
									currentYOffset += textHeight + (textPaddingY * 2);
								}
							} break;
							case ValueType::INT: {
								// Text and background
								{
									char str[10];
									sprintf_s(str, 10, "%i", setting->value->_int);
									std::string text = str;

									char name[0x22];
									sprintf_s(name, "%s: ", setting->name);
									if (name[0] != 0)
										name[0] = toupper(name[0]);
									std::string elTexto = name + text;

									windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 5 /* because we add 5 to text padding*/);
									DrawUtils::drawText(textPos, &elTexto, whiteColor, textSize);
									currentYOffset += textPaddingY + textHeight;
									rectPos.w = currentYOffset;
									DrawUtils::fillRectangle(rectPos, Mc_Color(18, 18, 18), backgroundAlpha);
								}
								if ((currentYOffset - ourWindow->pos.y) > (Game.getGuiData()->heightGame * 0.75)) {
									overflowing = true;
									break;
								}
								// Slider
								{
									Vec4 rect = Vec4(
										currentXOffset + textPaddingX + 5,
										currentYOffset + textPaddingY,
										xEnd - textPaddingX,
										currentYOffset - textPaddingY + textHeight);

									// Visuals & Logic
									{
										rectPos.y = currentYOffset;
										rectPos.w += textHeight + (textPaddingY * 2);
										// Background
										const bool areWeFocused = rect.contains(&mousePos);
										DrawUtils::fillRectangle(rectPos, Mc_Color(18, 18, 18), backgroundAlpha);
										DrawUtils::drawRectangle(rect, whiteColor, 1.f, backgroundAlpha);  // Slider background

										const float minValue = (float)setting->minValue->_int;
										const float maxValue = (float)setting->maxValue->_int - minValue;
										float value = (float)fmax(0, setting->value->_int - minValue);  // Value is now always > 0 && < maxValue
										if (value > maxValue)
											value = maxValue;
										value /= maxValue;  // Value is now in range 0 - 1
										const float endXlol = (xEnd - textPaddingX) - (currentXOffset + textPaddingX + 5);
										value *= endXlol;  // Value is now pixel diff between start of bar and end of progress

										// Draw Progress
										{
											rect.z = rect.x + value;
											DrawUtils::fillRectangle(rect, Mc_Color(50, 50, 50), (areWeFocused || setting->isDragging) ? 1.f : 0.8f);
										}

										// Drag Logic
										{
											if (setting->isDragging) {
												if (DrawUtils::isLeftClickDown && !DrawUtils::isRightClickDown)
													value = mousePos.x - rect.x;
												else
													setting->isDragging = false;
											} else if (areWeFocused && DrawUtils::shouldToggleLeftClick && !ourWindow->isInAnimation) {
												DrawUtils::shouldToggleLeftClick = false;
												setting->isDragging = true;
											}
										}

										// Save Value
										{
											value /= endXlol;  // Now in range 0 - 1
											value *= maxValue;
											value += minValue;

											setting->value->_int = (int)roundf(value);
											setting->makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt();
										}
									}
									currentYOffset += textHeight + (textPaddingY * 2);
								}
							} break;
							default: {
								char alc[100];
								sprintf_s(alc, 100, "Not implemented (%s)", setting->name);
								std::string elTexto = alc;
								// Adjust window size if our text is too  t h i c c
								windowSize->x = fmax(windowSize->x, DrawUtils::getTextWidth(&elTexto, textSize) + 5 /* because we add 5 to text padding*/);

								DrawUtils::drawText(textPos, &elTexto, whiteColor, textSize);
								currentYOffset += textHeight + (textPaddingY * 2);
							} break;
							}
						}
						float endYOffset = currentYOffset;
						if (endYOffset - startYOffset > textHeight + 1 || overflowing) {
							startYOffset += textPaddingY;
							endYOffset -= textPaddingY;
							DrawUtils::setColor(1, 1, 1, 1);
							DrawUtils::drawLine(Vec2(currentXOffset + 2, startYOffset), Vec2(currentXOffset + 2, endYOffset), 0.5f);
						}
					}
				} else
					currentYOffset += textHeight + (textPaddingY * 2);
			}
		}

		Vec4 winRectPos = Vec4(
			xOffset,
			yOffset,
			xEnd,
			currentYOffset);

		if (winRectPos.contains(&mousePos)) {
			if (scrollingDirection > 0 && overflowing) {
				ourWindow->yOffset += scrollingDirection;
			} else if (scrollingDirection < 0) {
				ourWindow->yOffset += scrollingDirection;
			}
			scrollingDirection = 0;
			if (ourWindow->yOffset < 0) {
				ourWindow->yOffset = 0;
			}
		}
	}
	DrawUtils::flush();
	// Draw Category Header
	{
		Vec2 textPos = Vec2(
			currentXOffset + textPaddingX,
			categoryHeaderYOffset + textPaddingY);
		Vec4 rectPos = Vec4(
			currentXOffset - categoryMargin,
			categoryHeaderYOffset - categoryMargin,
			currentXOffset + windowSize->x + paddingRight + categoryMargin,
			categoryHeaderYOffset + textHeight + (textPaddingY * 2));

		// Extend Logic
		{
			if (rectPos.contains(&mousePos) && DrawUtils::shouldToggleRightClick && !isDragging) {
				DrawUtils::shouldToggleRightClick = false;
				ourWindow->isExtended = !ourWindow->isExtended;
				if (ourWindow->isExtended && ourWindow->animation == 0)
					ourWindow->animation = 0.002f;
				else if (!ourWindow->isExtended && ourWindow->animation == 1)
					ourWindow->animation = 0;
				ourWindow->isInAnimation = true;

				for (auto& mod : moduleList) {
					std::shared_ptr<ClickModule> clickMod = getClickModule(ourWindow, mod->getRawModuleName());
					clickMod->isExtended = false;
				}
			}
		}

		// Dragging Logic
		{
			if (isDragging && Utils::getCrcHash(categoryName) == draggedWindow) {  // WE are being dragged
				if (DrawUtils::isLeftClickDown) {                                      // Still dragging
					Vec2 diff = Vec2(mousePos).sub(dragStart);
					ourWindow->pos = ourWindow->pos.add(diff);
					dragStart = mousePos;
				} else {  // Stopped dragging
					isDragging = false;
				}
			} else if (rectPos.contains(&mousePos) && DrawUtils::shouldToggleLeftClick) {
				isDragging = true;
				draggedWindow = Utils::getCrcHash(categoryName);
				DrawUtils::shouldToggleLeftClick = false;
				dragStart = mousePos;
			}
		}

		// Draw category component
		{
			// Draw Text
			std::string textStr = categoryName;
			auto clickguiMod = moduleMgr->getModule<ClickGuiMod>();
			DrawUtils::drawText(textPos, &textStr, whiteColor, textSize);
			DrawUtils::fillRectangle(rectPos, moduleColor, 0.40f);
			DrawUtils::fillRectangle(Vec4(rectPos.x, rectPos.w - 1, rectPos.z, rectPos.w), Mc_Color(184, 0, 255), 1 - ourWindow->animation);
			
			// Draw Dash
			if (clickguiMod->mode.selected == 0) {
				if (!ourWindow->isExtended)
					GuiUtils::drawDownArrow(Vec2(currentXOffset + windowSize->x + paddingRight - 5.5f, categoryHeaderYOffset + textPaddingY + (textHeight / 3)), whiteColor, ArrowWidth, ArrowSize);
				else
					GuiUtils::drawUpArrow(Vec2(currentXOffset + windowSize->x + paddingRight - 5.5f, categoryHeaderYOffset + textPaddingY + (textHeight / 1.5)), whiteColor, ArrowWidth, ArrowSize);
			} else {
				GuiUtils::drawCrossLine(Vec2(currentXOffset + windowSize->x + paddingRight - (crossSize / 2) - 1.f, categoryHeaderYOffset + textPaddingY + (textHeight / 2)), whiteColor, crossWidth, crossSize, !ourWindow->isExtended);
			}
		}
	}

	// anti idiot
	{
		Vec2 windowSize = Game.getClientInstance()->getGuiData()->windowSize;

		if (ourWindow->pos.x + ourWindow->size.x > windowSize.x) {
			ourWindow->pos.x = windowSize.x - ourWindow->size.x;
		}

		if (ourWindow->pos.y + ourWindow->size.y > windowSize.y) {
			ourWindow->pos.y = windowSize.y - ourWindow->size.y;
		}

		ourWindow->pos.x = (float)fmax(0, ourWindow->pos.x);
		ourWindow->pos.y = (float)fmax(0, ourWindow->pos.y);
	}

	moduleList.clear();
	DrawUtils::flush();
}

void ClickGui::render() {
	if (!moduleMgr->isInitialized())
		return;

	if (timesRendered < 10)
		timesRendered++;

	static auto clickGuiMod = moduleMgr->getModule<ClickGuiMod>();

	if (clickGuiMod->Opacity < 60)
		clickGuiMod->Opacity++;

	// Fill Background
	DrawUtils::fillRectangle(Vec4(0, 0, Game.getGuiData()->widthGame, Game.getGuiData()->heightGame), Mc_Color(0, 0, 0), clickGuiMod->Opacity / 100.f);


	// Render all categorys
	renderCategory(Category::COMBAT);
	renderCategory(Category::RENDER);
	renderCategory(Category::MOVEMENT);
	renderCategory(Category::PLAYER);
	renderCategory(Category::ENTITY);
	renderCategory(Category::MISC);
	renderCategory(Category::WORLD);
	renderCategory(Category::HUD);

	DrawUtils::shouldToggleLeftClick = false;
	DrawUtils::shouldToggleRightClick = false;
	resetStartPos = false;

	DrawUtils::flush();
}

void ClickGui::init() { initialised = true; }

void ClickGui::onWheelScroll(bool direction) {
	if (!direction) 
		scrollingDirection++;
	 else 
		scrollingDirection--;
}

void ClickGui::onKeyUpdate(int key, bool isDown) {
	 if (!initialised || !isDown)
		return;

	 static auto clickGuiMod = moduleMgr->getModule<ClickGuiMod>();

	 if (!clickGuiMod->isEnabled()) {
		timesRendered = 0;
		return;
	 }

	 if (timesRendered < 10)
		return;

	 timesRendered = 0;

	 switch (key) {
	 case VK_ESCAPE:
		clickGuiMod->setEnabled(false);
		return;
	 default:
		if (key == clickGuiMod->getKeybind())
			clickGuiMod->setEnabled(false);
	 }
}
using json = nlohmann::json;
void ClickGui::onLoadConfig(void* confVoid) {
	savedWindowSettings.clear();
	windowMap.clear();
	json* conf = reinterpret_cast<json*>(confVoid);
	if (conf->contains("ClickGuiMenu")) {
		auto obj = conf->at("ClickGuiMenu");
		if (obj.is_null())
			return;
		for (int i = 0; i <= (int)Category::HUD /*last category*/; i++) {
			auto catName = ClickGui::catToName((Category)i);
			if (obj.contains(catName)) {
				auto value = obj.at(catName);
				if (value.is_null())
					continue;
				try {
					SavedWindowSettings windowSettings = {};
					windowSettings.name = catName;
					if (value.contains("pos")) {
						auto posVal = value.at("pos");
						if (!posVal.is_null() && posVal.contains("x") && posVal["x"].is_number_float() && posVal.contains("y") && posVal["y"].is_number_float()) {
							try {
								windowSettings.pos = {posVal["x"].get<float>(), posVal["y"].get<float>()};
							} catch (std::exception e) {
							}
						}
					}
					if (value.contains("isExtended")) {
						auto isExtVal = value.at("isExtended");
						if (!isExtVal.is_null() && isExtVal.is_boolean()) {
							try {
								windowSettings.isExtended = isExtVal.get<bool>();
							} catch (std::exception e) {
							}
						}
					}
					savedWindowSettings[Utils::getCrcHash(catName)] = windowSettings;
				} catch (std::exception e) {
					logF("Config Load Error (ClickGuiMenu): %s", e.what());
				}
			}
		}
	}
}
void ClickGui::onSaveConfig(void* confVoid) {
	json* conf = reinterpret_cast<json*>(confVoid);
	// First update our map
	for (const auto& wind : windowMap) {
		savedWindowSettings[wind.first] = {wind.second->pos, wind.second->isExtended, wind.second->name};
	}

	// Save to json
	if (conf->contains("ClickGuiMenu"))
		conf->erase("ClickGuiMenu");

	json obj = {};

	for (const auto& wind : savedWindowSettings) {
		json subObj = {};
		subObj["pos"]["x"] = wind.second.pos.x;
		subObj["pos"]["y"] = wind.second.pos.y;
		subObj["isExtended"] = wind.second.isExtended;
		obj[wind.second.name] = subObj;
	}

	conf->emplace("ClickGuiMenu", obj);
}
