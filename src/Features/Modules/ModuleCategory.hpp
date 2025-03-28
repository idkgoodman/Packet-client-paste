//
// Created by vastrakai on 6/28/2024.
//

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

enum class ModuleCategory {
    Combat,
    Movement,
    Player,
    Render,
    Other
};

static std::vector<std::string> ModuleCategoryNames = {
    "Combat",
    "Movement",
    "Player",
    "Render",
    "Other"
};

static std::unordered_map<std::string, int> ModuleCategoryMap = {
    {"Combat", static_cast<int>(ModuleCategory::Combat)},
    {"Movement", static_cast<int>(ModuleCategory::Movement)},
    {"Player", static_cast<int>(ModuleCategory::Player)},
    {"Visual", static_cast<int>(ModuleCategory::Render)},
    {"Misc", static_cast<int>(ModuleCategory::Other)}
};