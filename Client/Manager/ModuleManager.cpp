#include "ModuleManager.h"
#include "../../Utils/Logging.h"

using json = nlohmann::json;

ModuleManager::ModuleManager(GameData* gameData) {
	gameData = gameData;
}

ModuleManager::~ModuleManager() {
	initialized = false;
	moduleList.clear();
}

void ModuleManager::initModules() {
	Log("Initializing modules.");
	{
		moduleList.emplace_back(new FollowPathModule());
		// moduleList.emplace_back(new InventoryCleaner());
		// moduleList.emplace_back(new StackableItem());
		moduleList.emplace_back(new InventoryMove());
		moduleList.emplace_back(new AntiImmobile());
		// moduleList.emplace_back(new ChestStealer());
		moduleList.emplace_back(new ToggleSounds());
		moduleList.emplace_back(new MinecraftRGB());
		moduleList.emplace_back(new Watermark());
		// moduleList.emplace_back(new OffhandAllow());
		moduleList.emplace_back(new EditionFaker());
		moduleList.emplace_back(new FontChanger());
		moduleList.emplace_back(new TimeChanger());
		// moduleList.emplace_back(new CrystalAura());
		moduleList.emplace_back(new AutoClicker());
		moduleList.emplace_back(new ClickGuiMod());
		moduleList.emplace_back(new BlockReach());
		moduleList.emplace_back(new FastLadder());
		moduleList.emplace_back(new FullBright());
		// moduleList.emplace_back(new NoSlowDown());
		moduleList.emplace_back(new InstaBreak());
		moduleList.emplace_back(new AutoSprint());
		moduleList.emplace_back(new RainbowSky());
		moduleList.emplace_back(new ServerInfo());
		moduleList.emplace_back(new StorageESP());
		moduleList.emplace_back(new TriggerBot());
		moduleList.emplace_back(new KeyStrokes());
		moduleList.emplace_back(new AntiInvis());
		moduleList.emplace_back(new ViewModel());
		moduleList.emplace_back(new ArmourHud());
		moduleList.emplace_back(new Waypoints());
		moduleList.emplace_back(new Arraylist());
		moduleList.emplace_back(new NoHurtcam());
		moduleList.emplace_back(new AutoSneak());
		moduleList.emplace_back(new NightMode());
		// moduleList.emplace_back(new ChestAura());
		moduleList.emplace_back(new NoFriends());
		// moduleList.emplace_back(new AutoArmor());
		moduleList.emplace_back(new AutoTotem());
		// moduleList.emplace_back(new BowAimbot());
		moduleList.emplace_back(new Criticals());
		moduleList.emplace_back(new TargetHUD()); // Recode this
		// moduleList.emplace_back(new Disabler());
		moduleList.emplace_back(new FastStop());
		moduleList.emplace_back(new Freelook());
		moduleList.emplace_back(new Teleport());
		moduleList.emplace_back(new MidClick());
		moduleList.emplace_back(new AntiVoid());
		moduleList.emplace_back(new NameTags());
		// moduleList.emplace_back(new HighJump());
		moduleList.emplace_back(new NoPacket());
		moduleList.emplace_back(new Scaffold());
		moduleList.emplace_back(new Velocity());
		moduleList.emplace_back(new Killaura());
		moduleList.emplace_back(new FastUse());
		moduleList.emplace_back(new Compass());
		// moduleList.emplace_back(new AutoPot());
		moduleList.emplace_back(new NoSwing());
		// moduleList.emplace_back(new Crasher());
		moduleList.emplace_back(new AntiBot());
		moduleList.emplace_back(new Spammer());
		moduleList.emplace_back(new AirSwim());
		moduleList.emplace_back(new Breaker());
		// moduleList.emplace_back(new Freecam());
		moduleList.emplace_back(new AirJump());
		// moduleList.emplace_back(new Spider());
		moduleList.emplace_back(new Hitbox());
		// moduleList.emplace_back(new NoFall());
		moduleList.emplace_back(new Tracer());
		moduleList.emplace_back(new Desync());
		// moduleList.emplace_back(new Aimbot());
		moduleList.emplace_back(new NewUI());
		moduleList.emplace_back(new Twerk());
		moduleList.emplace_back(new Radar());
		moduleList.emplace_back(new Teams());
		moduleList.emplace_back(new Timer());
		// moduleList.emplace_back(new Tower());
		moduleList.emplace_back(new Jesus());
		moduleList.emplace_back(new NoWeb());
		moduleList.emplace_back(new Reach());
		moduleList.emplace_back(new Speed());
		moduleList.emplace_back(new Nuker());
		moduleList.emplace_back(new Blink());
		moduleList.emplace_back(new Phase());
		moduleList.emplace_back(new Glide());
		// moduleList.emplace_back(new Zoom());
		moduleList.emplace_back(new Trail());
		moduleList.emplace_back(new Derp());
		moduleList.emplace_back(new Bhop());
		moduleList.emplace_back(new Xray());
		moduleList.emplace_back(new Step());
		moduleList.emplace_back(new Fly());
		moduleList.emplace_back(new ESP());
		moduleList.emplace_back(new FPS());
		moduleList.emplace_back(new BPS());
		moduleList.emplace_back(new CPS());
		moduleList.emplace_back(new XP());
		// Movement
		moduleList.emplace_back(new BoatFly());
		// Entity
		moduleList.emplace_back(new EntityLongJump());
		moduleList.emplace_back(new EntitySpider());
		moduleList.emplace_back(new EntityJesus());
		moduleList.emplace_back(new EntitySpeed());
		moduleList.emplace_back(new EntityBhop());
		moduleList.emplace_back(new EntityFly());

#ifdef _DEBUG
		moduleList.emplace_back(new PacketLogger());
		moduleList.emplace_back(new VanillaPlus());
		moduleList.emplace_back(new TestModule());
#endif

		// Sort modules alphabetically
		std::sort(moduleList.begin(), moduleList.end(), [](auto lhs, auto rhs) {
			auto current = lhs;
			auto other = rhs;
			return std::string{*current->getModuleName()} < std::string{*other->getModuleName()};
		});

		initialized = true;
	}
	
	getModule<ClickGuiMod>()->setEnabled(false);
	getModule<Arraylist>()->setEnabled(true);
	getModule<AntiBot>()->setEnabled(true);
}

void ModuleManager::disable() {
	for (auto& mod : moduleList) {
		if (mod->isEnabled())
			mod->setEnabled(false);
	}
}

void ModuleManager::onLoadConfig(void* confVoid) {
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized())
		return;
	for (auto& mod : moduleList) {
		mod->onLoadConfig(conf);
	}

	getModule<ClickGuiMod>()->setEnabled(false);
	getModule<Arraylist>()->setEnabled(true);
	getModule<AntiBot>()->setEnabled(true);
}

void ModuleManager::onSaveConfig(void* confVoid) {
	auto conf = reinterpret_cast<json*>(confVoid);
	if (!isInitialized())
		return;
	for (auto& mod : moduleList) {
		mod->onSaveConfig(conf);
	}
}

void ModuleManager::onImGuiRender() {
	if (!isInitialized())
		return;
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onImGuiRender();
	}
}

void ModuleManager::onWorldTick(GameMode* gameMode) {
	if (!isInitialized())
		return;
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onWorldTick(gameMode);
	}
}

void ModuleManager::onTick(GameMode* gameMode) {
	if (!isInitialized())
		return;
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onTick(gameMode);
	}
}

void ModuleManager::onAttack(Entity* attackEnt) {
	if (!isInitialized())
		return;
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onAttack(attackEnt);
	}
}

void ModuleManager::onKeyUpdate(int key, bool isDown) {
	if (!isInitialized())
		return;
	for (auto& mod : moduleList) {
		mod->onKeyUpdate(key, isDown);
	}
}

void ModuleManager::onKey(int key, bool isDown, bool& shouldCancel) {
	if (!isInitialized())
		return;
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onKey(key, isDown, shouldCancel);
	}
}

void ModuleManager::onPreRender(MinecraftUIRenderContext* renderCtx) {
	if (!isInitialized())
		return;
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPreRender(renderCtx);
	}
}

void ModuleManager::onPostRender(MinecraftUIRenderContext* renderCtx) {
	if (!isInitialized())
		return;
	for (auto& mod : moduleList) {
		if (mod->isEnabled() || mod->callWhenDisabled())
			mod->onPostRender(renderCtx);
	}
}

void ModuleManager::onSendClientPacket(Packet* packet) {
	if (!isInitialized())
		return;
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onSendClientPacket(packet);
	}
}

void ModuleManager::onSendPacket(Packet* packet) {
	if (!isInitialized())
		return;
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onSendPacket(packet);
	}
}

void ModuleManager::onBaseTick(Entity* ent) {
	if (!isInitialized())
		return;
	for (auto& mod : moduleList) {
		mod->onBaseTick(ent);
	}
}

std::vector<std::shared_ptr<Module>>* ModuleManager::getModuleList() {
	return &moduleList;
}

int ModuleManager::getModuleCount() {
	return (int)moduleList.size();
}

int ModuleManager::getEnabledModuleCount() {
	int i = 0;
	for (auto& it : moduleList) {
		if (it->isEnabled()) i++;
	}
	return i;
}
void ModuleManager::onMove(MoveInputHandler* hand) {
	if (!isInitialized())
		return;
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onMove(hand);
	}
}

void ModuleManager::onPlayerTick(Player* player) {
	if (!isInitialized())
		return;
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onPlayerTick(player);
	}
}
void ModuleManager::onLevelRender() {
	if (!isInitialized())
		return;
	for (auto& it : moduleList) {
		if (it->isEnabled() || it->callWhenDisabled())
			it->onLevelRender();
	}
}

ModuleManager* moduleMgr = new ModuleManager(&Game);
