//
// Created by vastrakai on 6/28/2024.
//

#include <build_info.h>
#include <Features/Modules/ModuleManager.hpp>
#include <Utils/OAuthUtils.hpp>
#include <Module.hpp>

#include "Combat/Aura.hpp"
#include "Combat/AutoClicker.hpp"
#include "Combat/Criticals.hpp"
#include "Combat/InfiniteAura.hpp"
#include "Combat/Reach.hpp"
#include "Combat/TriggerBot.hpp"
#include "Combat/AimAssist.hpp"
#include "Combat/AntiBot.hpp"
#include "Combat/AutoPot.hpp"
#include "Combat/Regen.hpp"
#include "Combat/TargetStrafe.hpp"
#include "Combat/Velocity.hpp"
#include "Combat/Teams.hpp"

#include "Other/AutoAccept.hpp"
#include "Other/AutoHive.hpp"
#include "Other/AutoQueue.hpp"
#include "Other/AutoVote.hpp"
#include "Other/Breaker.hpp"
#include "Other/Desync.hpp"
#include "Other/DeviceSpoof.hpp"
#include "Other/Disabler.hpp"
#include "Other/Friends.hpp"
#include "Other/KickSounds.hpp"
#include "Other/Killsults.hpp"
#include "Other/MCF.hpp"
#include "Other/MCP.hpp"
#include "Other/NetSkip.hpp"
#include "Other/NoFilter.hpp"
#include "Other/NoPacket.hpp"
#include "Other/Spammer.hpp"
#include "Other/StaffAlert.hpp"

#include "Movement/AntiImmobile.hpp"
#include "Movement/FastStop.hpp"
#include "Movement/Fly.hpp"
#include "Movement/InvMove.hpp"
#include "Movement/Jesus.hpp"
#include "Movement/LongJump.hpp"
#include "Movement/Phase.hpp"
#include "Movement/SafeWalk.hpp"
#include "Movement/Speed.hpp"
#include "Movement/Spider.hpp"
#include "Movement/Sprint.hpp"
#include "Movement/Step.hpp"
#include "Movement/NoSlow.hpp"

#include "Player/AntiVoid.hpp"
#include "Player/AutoBoombox.hpp"
#include "Player/AutoTool.hpp"
#include "Player/ChestAura.hpp"
#include "Player/Stealer.hpp"
#include "Player/Derp.hpp"
#include "Player/Extinguisher.hpp"
#include "Player/FastMine.hpp"
#include "Player/Freecam.hpp"
#include "Player/Manager.hpp"
#include "Player/NoFall.hpp"
#include "Player/NoRotate.hpp"
#include "Player/Nuker.hpp"
#include "Player/OreBreaker.hpp"
#include "Player/Scaffold.hpp"
#include "Player/Timer.hpp"
#include "Player/FastEat.hpp"

#include "spdlog/spdlog.h"

#include "Render/Ambience.hpp"
#include "Render/Animations.hpp"
#include "Render/Arraylist.hpp"
#include "Render/AutoScale.hpp"
#include "Render/BabyBoy.hpp"
#include "Render/BlockESP.hpp"
#include "Render/CameraClip.hpp"
#include "Render/ClickGui.hpp"
#include "Render/Chat.hpp"
#include "Render/Counters.hpp"
#include "Render/ESP.hpp"
#include "Render/FullBright.hpp"
#include "Render/Glint.hpp"
#include "Render/HitEffects.hpp"
#include "Render/HPBar.hpp"
#include "Render/HudEditor.hpp"
#include "Render/Interface.hpp"
#include "Render/ItemESP.hpp"
#include "Render/ItemPhysics.hpp"
#include "Render/Keystrokes.hpp"
#include "Render/LevelInfo.hpp"
#include "Render/MotionBlur.hpp"
#include "Render/NameProtect.hpp"
#include "Render/Nametags.hpp"
#include "Render/NoDebuff.hpp"
#include "Render/NoHurtcam.hpp"
#include "Render/NoRender.hpp"
#include "Render/Notifications.hpp"
#include "Render/RobloxCamera.hpp"
#include "Render/SessionInfo.hpp"
#include "Render/TargetHUD.hpp"
#include "Render/ViewModel.hpp"
#include "Render/Watermark.hpp"
#include "Render/Zoom.hpp"
#include "Render/Statistics.hpp"
#include "Render/PlayerList.hpp"

void ModuleManager::init()
{
    // Render (must be initialized first)
    mModules.emplace_back(std::make_shared<HudEditor>());

    // Combat
    mModules.emplace_back(std::make_shared<Aura>());
    mModules.emplace_back(std::make_shared<AimAssist>());
    mModules.emplace_back(std::make_shared<AntiBot>());
    mModules.emplace_back(std::make_shared<AutoPot>());
    mModules.emplace_back(std::make_shared<TriggerBot>());
    mModules.emplace_back(std::make_shared<AutoClicker>());
    mModules.emplace_back(std::make_shared<Reach>());
    mModules.emplace_back(std::make_shared<Criticals>());
    mModules.emplace_back(std::make_shared<InfiniteAura>());
    mModules.emplace_back(std::make_shared<Regen>());
    mModules.emplace_back(std::make_shared<TargetStrafe>());
    mModules.emplace_back(std::make_shared<Teams>());
    mModules.emplace_back(std::make_shared<Velocity>());


    // Movement
    mModules.emplace_back(std::make_shared<Fly>());
    mModules.emplace_back(std::make_shared<Velocity>());
    mModules.emplace_back(std::make_shared<NoSlow>());
    mModules.emplace_back(std::make_shared<AntiImmobile>());
    mModules.emplace_back(std::make_shared<Sprint>());
    mModules.emplace_back(std::make_shared<Speed>());
    mModules.emplace_back(std::make_shared<InvMove>());
    mModules.emplace_back(std::make_shared<SafeWalk>());
    mModules.emplace_back(std::make_shared<Phase>());
    mModules.emplace_back(std::make_shared<FastStop>());
    mModules.emplace_back(std::make_shared<Step>());
    mModules.emplace_back(std::make_shared<LongJump>());
    mModules.emplace_back(std::make_shared<TargetStrafe>());
    mModules.emplace_back(std::make_shared<Jesus>());


    // Player
    mModules.emplace_back(std::make_shared<Timer>());
    mModules.emplace_back(std::make_shared<Stealer>());
    mModules.emplace_back(std::make_shared<Manager>());
    mModules.emplace_back(std::make_shared<Scaffold>());
    mModules.emplace_back(std::make_shared<Nuker>());
    mModules.emplace_back(std::make_shared<OreBreaker>());
    mModules.emplace_back(std::make_shared<AutoBoombox>());
    mModules.emplace_back(std::make_shared<AutoTool>());
    mModules.emplace_back(std::make_shared<Derp>());
    mModules.emplace_back(std::make_shared<Freecam>());
    mModules.emplace_back(std::make_shared<NoFall>());
    mModules.emplace_back(std::make_shared<AntiVoid>());
    mModules.emplace_back(std::make_shared<Extinguisher>());
    mModules.emplace_back(std::make_shared<FastMine>());
    mModules.emplace_back(std::make_shared<ChestAura>());
    mModules.emplace_back(std::make_shared<NoRotate>());
    mModules.emplace_back(std::make_shared<FastEat>());

    // Other
    mModules.emplace_back(std::make_shared<AutoHive>());
    mModules.emplace_back(std::make_shared<Breaker>());
    mModules.emplace_back(std::make_shared<Desync>());
    mModules.emplace_back(std::make_shared<MCF>());
    mModules.emplace_back(std::make_shared<MCP>());
    mModules.emplace_back(std::make_shared<ToggleSounds>());
    mModules.emplace_back(std::make_shared<DeviceSpoof>());
    mModules.emplace_back(std::make_shared<EditionFaker>());
    mModules.emplace_back(std::make_shared<KickSounds>());
    mModules.emplace_back(std::make_shared<AutoQueue>());
    mModules.emplace_back(std::make_shared<Friends>());
    mModules.emplace_back(std::make_shared<NoPacket>());
    mModules.emplace_back(std::make_shared<NoFilter>());
    mModules.emplace_back(std::make_shared<Killsults>());
    mModules.emplace_back(std::make_shared<NetSkip>());
    mModules.emplace_back(std::make_shared<Disabler>());
    mModules.emplace_back(std::make_shared<AutoReport>());
    mModules.emplace_back(std::make_shared<StaffAlert>());
    mModules.emplace_back(std::make_shared<AutoAccept>());
    mModules.emplace_back(std::make_shared<Spammer>());
    mModules.emplace_back(std::make_shared<AutoVote>());


    // Render
    mModules.emplace_back(std::make_shared<Ambience>());
    mModules.emplace_back(std::make_shared<BabyBoy>());
    mModules.emplace_back(std::make_shared<Watermark>());
    mModules.emplace_back(std::make_shared<ClickGui>());
    mModules.emplace_back(std::make_shared<AutoScale>());
    mModules.emplace_back(std::make_shared<Interface>());
    mModules.emplace_back(std::make_shared<Arraylist>());
    mModules.emplace_back(std::make_shared<Notifications>());
    mModules.emplace_back(std::make_shared<DestroyProgress>());
    mModules.emplace_back(std::make_shared<ESP>());
    mModules.emplace_back(std::make_shared<BlockESP>());
    mModules.emplace_back(std::make_shared<MotionBlur>());
    mModules.emplace_back(std::make_shared<Animations>());
    mModules.emplace_back(std::make_shared<CameraClip>());
    mModules.emplace_back(std::make_shared<Counters>());
    mModules.emplace_back(std::make_shared<TargetInfo>());
    mModules.emplace_back(std::make_shared<ItemESP>());
    mModules.emplace_back(std::make_shared<Nametags>());
    mModules.emplace_back(std::make_shared<NoHurtcam>());
    mModules.emplace_back(std::make_shared<FullBright>());
    mModules.emplace_back(std::make_shared<Keystrokes>());
    mModules.emplace_back(std::make_shared<ViewModel>());
    mModules.emplace_back(std::make_shared<NameProtect>());
    mModules.emplace_back(std::make_shared<Zoom>());
    mModules.emplace_back(std::make_shared<Glint>());
    mModules.emplace_back(std::make_shared<NoDebuff>());
    mModules.emplace_back(std::make_shared<JumpCircles>());
    mModules.emplace_back(std::make_shared<Freelook>());
    mModules.emplace_back(std::make_shared<NoRender>());
    mModules.emplace_back(std::make_shared<Chat>());
    mModules.emplace_back(std::make_shared<HitEffects>());
    mModules.emplace_back(std::make_shared<HPBar>());
    mModules.emplace_back(std::make_shared<HudEditor>());
    mModules.emplace_back(std::make_shared<ItemPhysics>());
    mModules.emplace_back(std::make_shared<Statistics>());
    mModules.emplace_back(std::make_shared<PlayerList>());


void ModuleManager::shutdown()
{
    for (auto& module : mModules)
    {
        if (module->mEnabled)
        {
            module->mEnabled = false;
            module->onDisable();
        }
    }

    mModules.clear();
}

void ModuleManager::registerModule(const std::shared_ptr<Module>& module)
{
    mModules.push_back(module);
}

std::vector<std::shared_ptr<Module>>& ModuleManager::getModules()
{
    return mModules;
}

Module* ModuleManager::getModule(const std::string& name) const
{
    for (const auto& module : mModules)
    {
        if (StringUtils::equalsIgnoreCase(module->mName, name))
        {
            return module.get();
        }
    }
    return nullptr;
}

void ModuleManager::removeModule(const std::string& name)
{
    for (auto it = mModules.begin(); it != mModules.end(); ++it)
    {
        if (StringUtils::equalsIgnoreCase((*it)->mName, name))
        {
            mModules.erase(it);
            return;
        }
    }
}

std::vector<std::shared_ptr<Module>>& ModuleManager::getModulesInCategory(int catId)
{
    static std::unordered_map<int, std::vector<std::shared_ptr<Module>>> categoryMap = {};
    if (categoryMap.contains(catId))
    {
        return categoryMap[catId];
    }

    // Cache category
    std::vector<std::shared_ptr<Module>> modules;
    for (const auto& module : mModules)
    {
        if (static_cast<int>(module->mCategory) == catId)
        {
            modules.push_back(module);
        }
    }

    categoryMap[catId] = modules;
    return categoryMap[catId];
}

std::unordered_map<std::string, std::shared_ptr<Module>> ModuleManager::getModuleCategoryMap()
{
    static std::unordered_map<std::string, std::shared_ptr<Module>> map;

    if (!map.empty())
    {
        return map;
    }

    for (const auto& module : mModules)
    {
        map[module->getCategory()] = module;
    }

    return map;
}

void ModuleManager::onClientTick()
{
    for (auto& module : mModules)
    {
        try
        {
            if (module->mWantedState != module->mEnabled)
            {
                module->mEnabled = module->mWantedState;
                spdlog::trace("onClientTick: calling {} on module {}", module->mEnabled ? "onEnable" : "onDisable", module->mName);
                if (module->mEnabled)
                {
                    module->onEnable();
                }
                else
                {
                    module->onDisable();
                }
            }
        } catch (const std::exception& e)
        {
            spdlog::error("Failed to enable/disable module {}: {}", module->mName, e.what());
        } catch (const nlohmann::json::exception& e)
        {
            spdlog::error("Failed to enable/disable module {}: {}", module->mName, e.what());
        } catch (...)
        {
            spdlog::error("Failed to enable/disable module {}: unknown", module->mName);
        }
    }
}

nlohmann::json ModuleManager::serialize() const
{
    nlohmann::json j;
    j["client"] = "Solstice";
    j["version"] = SOLSTICE_VERSION;
    j["modules"] = nlohmann::json::array();

    for (const auto& module : mModules)
    {
        j["modules"].push_back(module->serialize());
    }

    return j;
}

nlohmann::json ModuleManager::serializeModule(Module* module)
{
    // same as above but only for the specified module
    nlohmann::json j;
    j["client"] = "Solstice";
    j["version"] = SOLSTICE_VERSION;
    j["modules"] = nlohmann::json::array();

    j["modules"].push_back(module->serialize());

    return j;
}

void ModuleManager::deserialize(const nlohmann::json& j, bool showMessages)
{
    // Get the version of the config
    const std::string version = j["version"];
    std::string currentVersion = SOLSTICE_VERSION;

    if (version != currentVersion)
    {
        spdlog::warn("Config version mismatch. Expected: {}, Got: {}", currentVersion, version);
        ChatUtils::displayClientMessage("§eWarning: The specified config is from a different version of Solstice. §cSome settings may not be loaded§e.");
    }

    int modulesLoaded = 0;
    int settingsLoaded = 0;
    // Get names of all modules in the moduleManager
    std::vector<std::string> moduleNames;
    for (const auto& module : mModules)
    {
        moduleNames.push_back(module->mName);
    }
    for (const auto& module : j["modules"])
    {
        const std::string name = module["name"];
        std::erase(moduleNames, name);
        const bool enabled = module["enabled"];
        const int keybind = module["key"];
        //const bool hideInArraylist = module["hideInArraylist"];

        auto* mod = getModule(name);
        if (mod)
        {
            mod->mWantedState = enabled;
            mod->mKey = keybind;
            //mod->mHideInArraylist = hideInArraylist;
            // Get the settings for the module
            std::vector<std::string> settingNames;
            for (const auto& setting : mod->mSettings)
            {
                settingNames.push_back(setting->mName);
            }
            if (module.contains("settings"))
            {
                for (const auto& setting : module["settings"].items())
                {
                    try
                    {
                        const auto& settingValue = setting.value();
                        const std::string settingName = settingValue["name"];
                        std::erase(settingNames, settingName);

                        auto* set = mod->getSetting(settingName);
                        if (set)
                        {
                            if (set->mType == SettingType::Bool)
                            {
                                auto* boolSetting = static_cast<BoolSetting*>(set);
                                boolSetting->mValue = settingValue["boolValue"];

                                if (settingValue.contains("key"))
                                {
                                    boolSetting->mKey = settingValue["key"];
                                }
                                else
                                {
                                    boolSetting->mKey = -1;
                                }
                            }
                            else if (set->mType == SettingType::Number)
                            {
                                auto* numberSetting = static_cast<NumberSetting*>(set);
                                numberSetting->mValue = settingValue["numberValue"];
                            }
                            else if (set->mType == SettingType::Enum)
                            {
                                auto* enumSetting = static_cast<EnumSetting*>(set);
                                // Make sure the enum value is valid and within the bounds
                                if (settingValue["enumValue"] >= 0 && settingValue["enumValue"] < enumSetting->mValues.size())
                                    enumSetting->mValue = settingValue["enumValue"];
                                else
                                {
                                    spdlog::warn("Invalid enum value for setting {} in module {}", settingName, name);
                                    if (showMessages) ChatUtils::displayClientMessage("§cInvalid enum value for setting §6" + settingName + "§c in module §6" + name + "§c.");
                                }
                            } else if (set->mType == SettingType::Color)
                            {
                                auto* colorSetting = static_cast<ColorSetting*>(set);
                                // Get the  settingValue["colorValue"] as a float[4]
                                for (int i = 0; i < 4; i++)
                                {
                                    colorSetting->mValue[i] = settingValue["colorValue"][i];
                                }
                            }

                            settingsLoaded++;
                        } else
                        {
                            spdlog::warn("Setting {} not found for module {}", settingName, name);
                            if (showMessages) ChatUtils::displayClientMessage("§cSetting §6" + settingName + "§c not found for module §6" + name + "§c.");
                        }
                    } catch (const std::exception& e)
                    {
                        spdlog::warn("Failed to load setting {} for module {}: {}", setting.key(), name, e.what());
                        if (showMessages) ChatUtils::displayClientMessage("§cFailed to load setting §6" + setting.key() + "§c for module §6" + name + "§c.");
                    }
                }

                modulesLoaded++;
            }

            // If there are any settings left, log it
            for (const auto& settingName : settingNames)
            {
                spdlog::warn("Setting {} not found for module {}, default value will be used", settingName, name);
                if (showMessages) ChatUtils::displayClientMessage("§cSetting §6" + settingName + "§c not found for module §6" + name + "§c, default value will be used.");
            }
        } else
        {
            spdlog::warn("Module {} not found", name);
            if (showMessages) ChatUtils::displayClientMessage("§cModule §6" + name + "§c not found.");
        }
    }

    // If there are any modules left, log it
    for (const auto& moduleName : moduleNames)
    {
        spdlog::warn("Module {} not found in config, using default settings", moduleName);
        if (showMessages) ChatUtils::displayClientMessage("§cModule §6" + moduleName + "§c not found in config, using default settings.");
    }

    spdlog::info("Loaded {} modules and {} settings from config", modulesLoaded, settingsLoaded);
}
