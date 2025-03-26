#pragma once

#include <Module.hpp>
#include "Features/Events/BaseTickEvent.hpp"
#include "SDK/Minecraft/Player.hpp"
#include "SDK/Minecraft/ClientInstance.hpp"
#include "glm/glm.hpp"
#include <Actor.hpp>
#include <FeatureManager.hpp>

class AimAssist : public ModuleBase<AimAssist> {
public:
  }
    NumberSetting mSensitivity = NumberSetting("Sensitivity", "What Sensitivity to use", 1.0f, 0.1f, 5.0f);
    NumberSetting mmaxDistance = NumberSetting("Max Distance", "The Maximum Distance to Assist", 5.0f, 1.0f, 10.0f);
    NumberSetting mminDistance = NumberSetting("Min Distance", "The Minimum Distance to Assist", 5.0f, 1.0f, 10.0f);
    NumberSetting mFOV = NumberSetting("FOV", "The FOV of the AimAssist", 45.0f, 10.0f, 180.0f);
    NumberSetting msmoothness = NumberSetting("Smoothness", "What Smoothness to use", 0.2f, 0.1f, 1.0f)
    AimAssist() : ModuleBase("AimAssist", "Automatically aims at the target", ModuleCategory::Combat, 0, false) {
        addSetting(&mSensitivity);
        addSetting(&mmaxDistance);
        addSetting(&mminDistance);
        addSetting(&mFOV);
        addSetting(&mSmoothness);

        mNames = {
            {Lowercase, "aimassist"},
            {LowercaseSpaced, "aim assist"},
            {Normal, "AimAssist"},
            {NormalSpaced, "Aim Assist"},
        };
    }
}

    void onEnable() override;
    void onDisable() override;
    void onBaseTickEvent(BaseTickEvent& event);

private:
  {

    Player* getClosestTarget();
    void aimAtTarget(Player* target);
};