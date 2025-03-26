#pragma once
#include <Features/Modules/Module.hpp>
//
// Created by vastrakai on 7/2/2024.
//


class NoSlow : public ModuleBase<NoSlow> {
public:
    NoSlow() : ModuleBase("NoSlow", "Prevents you from being slowed down while walking through webs, using items, etc.", ModuleCategory::Movement, 0, false) {
        mNames = {
            {Lowercase, "noslow"},
            {LowercaseSpaced, "no slow"},
            {Normal, "NoSlow"},
            {NormalSpaced, "No Slow"}
        };
    }

    static void patchSlowdown(bool patch);
    void onEnable() override;
    void onDisable() override;
    void onBaseTickEvent(class BaseTickEvent& event);
    void onItemSlowdownEvent(class ItemSlowdownEvent& event);
};