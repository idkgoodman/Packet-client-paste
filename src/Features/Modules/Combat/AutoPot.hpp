#pragma once

#include "Features/Modules/Module.hpp"
#include "Features/Events/BaseTickEvent.hpp"
#include "SDK/Minecraft/ClientInstance.hpp"
#include "SDK/Minecraft/Player.hpp"
#include "SDK/Minecraft/Inventory.hpp"
#include "SDK/Minecraft/Item.hpp"

class AutoPot : public ModuleBase<AutoPot> {
public:
    AutoPot() : ModuleBase("AutoPot", "Automatically eat soups when needed", ModuleCategory::Combat, 0, false) {
        mNames = {
            {Lowercase, "autopot"},
            {LowercaseSpaced, "auto pot"},
            {Normal, "AutoPot"},
            {NormalSpaced, "Auto Pot"},
        };
    }

    void onEnable() override;
    void onDisable() override;
    void onBaseTickEvent(BaseTickEvent& event);

private:
    void useSoup();
};