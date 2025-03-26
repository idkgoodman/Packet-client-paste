#pragma once
//
// Created by vastrakai on 7/5/2024.
//

#include <Features/Modules/Module.hpp>
#include <SDK/Minecraft/Inventory/ContainerManagerModel.hpp>

class Stealer : public ModuleBase<Stealer> {
public:
    enum class Mode
    {
        Normal,
        Silent
    };

    EnumSettingT<Mode> mMode = EnumSettingT("Mode", "The mode of the chest stealer", Mode::Normal, "Normal", "Silent");
    BoolSetting mRandomizeDelay = BoolSetting("Randomize Delay", "Randomizes the delay between stealing items", false);
    NumberSetting mDelay = NumberSetting("Delay", "The delay between stealing items (in milliseconds)", 50, 0, 500, 1);
    NumberSetting mRandomizeMin = NumberSetting("Randomize Min", "The minimum delay to randomize", 50, 0, 500, 1);
    NumberSetting mRandomizeMax = NumberSetting("Randomize Max", "The maximum delay to randomize", 100, 0, 500, 1);
    BoolSetting mIgnoreUseless = BoolSetting("Ignore Useless", "Whether or not to ignore useless items", true);


    Stealer() : ModuleBase<Stealer>("Stealer", "Steals items from chests", ModuleCategory::Player, 0, false)
    {
        addSettings(
            &mMode,
            &mRandomizeDelay,
            &mDelay,
            &mRandomizeMin,
            &mRandomizeMax,
            &mIgnoreUseless
        );

        VISIBILITY_CONDITION(mRandomizeMin, mRandomizeDelay.mValue == true);
        VISIBILITY_CONDITION(mRandomizeMax, mRandomizeDelay.mValue == true);
        VISIBILITY_CONDITION(mDelay, mRandomizeDelay.mValue == false);

        mNames = {
            {Lowercase, "stealer"},
            {LowercaseSpaced, "stealer"},
            {Normal, "Stealer"},
            {NormalSpaced, "Stealer"}
        };
    }

    bool mIsStealing = false;
    uint64_t mLastItemTaken = 0;
    bool mIsChestOpen = false;
    std::vector<ItemStack> mItemsToTake = {};
    bool mTotalDirty = false;
    int mTotalItems = 0;
    int mRemainingItems = 0;
    glm::vec3 mLastPos = glm::vec3(0);
    glm::vec3 mHighlightedPos = glm::vec3(0);
    ContainerID mCurrentContainerId = ContainerID::None;
    uint64_t mLastOpen = 0;

    void onContainerScreenTickEvent(class ContainerScreenTickEvent& event) const;
    void reset();
    void onEnable() override;
    void onDisable() override;
    void takeItem(int slot, ItemStack& item);
    void takeItems(std::map<int, ItemStack>& items);
    void onBaseTickEvent(class BaseTickEvent& event);
    bool doDelay();
    void onRenderEvent(class RenderEvent& event);
    void onPacketOutEvent(class PacketOutEvent& event);
    void onPacketInEvent(class PacketInEvent& event);
    uint64_t getDelay() const;

    std::string getSettingDisplay() override {
        if (mRandomizeDelay.mValue)
        {
            return std::to_string(static_cast<int>(mRandomizeMin.mValue)) + " " + std::to_string(static_cast<int>(mRandomizeMax.mValue));
        }
        else
        {
            return std::to_string(static_cast<int>(mDelay.mValue)) + "";
        }
    }
};
