#pragma once
#include <Features/Modules/Module.hpp>
#include <string>
//
// Created by vastrakai on 7/2/2024.
//


class Arraylist : public ModuleBase<Arraylist>
{
public:

    enum class Mode {
        Bar,
        Split,
        None
    };

    enum class ModuleVisibility {
        All,
        Bound,
    };

    EnumSettingT<Mode> mMode = EnumSettingT("Mode", "Style of ArrayList", Display::Split, "Bar", "Split", "None");
    EnumSettingT<ModuleVisibility> mVisibility = EnumSettingT("Visibility", "Module visibility", ModuleVisibility::All, "All", "Bound");

    Arraylist() : ModuleBase("Arraylist", "Displays a list of modules", ModuleCategory::Render, 0, true) {
        addSettings(
            &mMode,
            &mVisibility,
        );

        VISIBILITY_CONDITION(mMode, mVisibility.mValue)

        mNames = {
            {Lowercase, "arraylist"},
            {LowercaseSpaced, "array list"},
            {Normal, "Arraylist"},
            {NormalSpaced, "Array List"}
        };
    }
    void onEnable() override;
    void onDisable() override;

    void onRenderEvent(class RenderEvent& event);
    std::string getSettingDisplay() override {
          return mMode.mValues[mMode.as<int>()];
    }
};