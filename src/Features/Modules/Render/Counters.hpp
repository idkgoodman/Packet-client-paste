#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Features/Modules/Module.hpp"
#include "ImGui/imgui.h"            // Для работы с ImGui (отрисовка элементов интерфейса)
#include "SDK/Minecraft/JSON.hpp"
#include "Features/FeatureManager.hpp" // Если используются события и менеджер фич
#include "Features/Events/RenderEvent.hpp"
#include "Features/Events/BaseTickEvent.hpp"
#include "Utils/MiscUtils/ImRenderUtils.hpp"
#include "imgui.h"
#include <ClientInstance.hpp>
#include <glfw3.h>


class Counters : public ModuleBase<Counters> {
public:
    BoolSettings mBPS = BoolStting("BPS", "Wether or not show BPS", true)
    BoolSettings mCPS = BoolSetting("CPS", "Wether or not show CPS", true)
    BoolSettings mFPS = BoolSetting("FPS", "Wether or not show FPS", false)

    Counters() : ModuleBase("Counters", "Displays FPS, BPS, or CPS", ModuleCategory::Render, 0, false) {
        addSettings(
            &mBPS,
            &mCPS,
            &mFPS
        };

        VISIBILITY_CONDITION(mBPS, mCPS.mValue)
        VISIBILITY_CONDITION(mFPS.mValue)

        mNames = {
            {Lowercase, "counters"},
            {LowercaseSpaced, "counters"},
            {Normal, "Counters"},
            {NormalSpaced, "Counters"},
        };



        mElement = std::make_unique<HudElement>();
        mElement->mPos = { 10, 0 }; // Начальная позиция
        mElement->mAnchor = HudElement::Anchor::MiddleLeft;
        const char* ModuleBaseType = ModuleBase<Counters>::getTypeID();
        mElement->mParentTypeIdentifier = const_cast<char*>(ModuleBaseType);
        mElement->mSize = glm::vec2(200, 150); // Размер худ элемента
        Counters::gClientInstance->registerElement(mElement.get());
    }

    std::unique_ptr<HudElement> mElement = nullptr;
    int fps = 0;
    int bps = 0;
    int cps = 0;
    int currentStat = 0; // Переключатель для FPS, BPS или CPS

    bool showFPS = true; // Флаг для отображения FPS
    bool showBPS = true; // Флаг для отображения BPS
    bool showCPS = true; // Флаг для отображения CPS

    void updateStatistics();
    void toggleStat(int stat);

    void onEnable() override;
    void onDisable() override;
    void onRenderEvent(class RenderEvent& event);
    void onBaseTickEvent(class BaseTickEvent& event);

private:
    // Добавим размытость фона
    void addBlurEffect(ImVec2 pos, ImVec2 size);
};