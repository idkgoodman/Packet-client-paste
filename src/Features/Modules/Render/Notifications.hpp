#pragma once
//
// Created by vastrakai on 7/4/2024.
//

#include <Features/FeatureManager.hpp>
#include <Features/Events/NotifyEvent.hpp>
#include <Features/Events/ModuleStateChangeEvent.hpp>
#include <Features/Events/ConnectionRequestEvent.hpp>
#include <Features/Events/RenderEvent.hpp>
#include <ImGui/ImGui.h>
#include <Module.hpp>
#include <vector>
#include <string>

class Notification {
public:
    enum class Type {
        Info,
        Warning,
        Error
    };

    std::string mMessage;
    Type mType;
    float mDuration;
    float mTimeShown;
    bool mIsTimeUp;
    float mCurrentDuration;

    Notification(std::string message, Type type, float duration)
        : mMessage(std::move(message)), mType(type), mDuration(duration), mTimeShown(0.f), mIsTimeUp(false), mCurrentDuration(0.f) {
    }
};

class Notifications : public ModuleBase<Notifications> {
public:
    enum class Style {
        Solaris,
    };

    EnumSettingT<Style> mStyle = EnumSettingT<Style>("Style", "The style of the notifications", Style::Solaris, "Solaris");
    BoolSetting mShowOnToggle = BoolSetting("Show on toggle", "Show a notification when a module is toggled", true);
    BoolSetting mShowOnJoin = BoolSetting("Show on join", "Show a notification when you join a server", true);
    BoolSetting mColorGradient = BoolSetting("Color gradient", "Enable a color gradient on the notifications", false);
    BoolSetting mLimitNotifications = BoolSetting("Limit notifications", "Limit the number of notifications shown at one time", false);
    NumberSetting mMaxNotifications = NumberSetting("Max notifications", "The maximum number of notifications shown at one time", 6, 1, 25, 1);

    Notifications() : ModuleBase("Notifications", "Shows notifications on module toggle and other events", ModuleCategory::Render, 0, true) {
        addSetting(&mStyle);
        addSetting(&mShowOnToggle);
        addSetting(&mShowOnJoin);
        //addSetting(&mColorGradient);
        addSetting(&mLimitNotifications);
        addSetting(&mMaxNotifications);
        VISIBILITY_CONDITION(mMaxNotifications, mLimitNotifications.mValue == true);

        mNames = {
            {Lowercase, "notifications"},
            {LowercaseSpaced, "notifications"},
            {Normal, "Notifications"},
            {NormalSpaced, "Notifications"}
        };

        gFeatureManager->mDispatcher->listen<RenderEvent, &Notifications::onRenderEvent, nes::event_priority::VERY_LAST>(this);
    }

    std::vector<Notification> mNotifications;

    void onEnable() override;
    void onDisable() override;
    void onRenderEvent(RenderEvent& event);
    void onModuleStateChange(ModuleStateChangeEvent& event);
    void onConnectionRequestEvent(ConnectionRequestEvent& event);
    void onNotifyEvent(NotifyEvent& event);

    std::string getSettingDisplay() override {
        return mStyle.mValues[mStyle.as<int>()];
    }
};
