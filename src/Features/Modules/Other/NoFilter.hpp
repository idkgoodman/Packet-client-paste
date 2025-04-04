#pragma once
//
// Created by vastrakai on 7/19/2024.
//

#include <Module.hpp>


class NoFilter : public ModuleBase<NoFilter> {
public:
    NoFilter() : ModuleBase("NoFilter", "Removes the chat filter.\nKeep in mind this will NOT bypass the serverside filter.", ModuleCategory::Other, 0, true)
    {
        mNames = {
            {Lowercase, "nofilter"},
            {LowercaseSpaced, "no filter"},
            {Normal, "NoFilter"},
            {NormalSpaced, "No Filter"}
        };
    }

    void onEnable() override;
    void onDisable() override;
};