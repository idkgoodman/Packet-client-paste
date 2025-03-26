#include "Arraylist.hpp"
#include "RenderEvent.hpp"
#include "ClientInstance.hpp"
#include "ModuleManager.hpp"
#include "ColorUtils.hpp"
#include <FeatureManager.hpp>
#include <imgui.h>
#include <string>

void Arraylist::onEnable() {
    // Инициализация для анимации включения
    mFadeProgress = 1.0f;  // Полная видимость при включении
}

void Arraylist::onDisable() {
    // Инициализация для анимации выключения
    mFadeProgress = 0.0f;  // Начинаем с нулевой видимости при выключении
}

void Arraylist::onRenderEvent(RenderEvent& event) {
    if (!gFeatureManager || !gFeatureManager->mModuleManager) return;

    auto* drawList = event.getDrawList();
    ImVec2 startPos = ImVec2(ImGui::GetIO().DisplaySize.x - 10, 10);
    float glowStrength = mGlowStrength.get(); // Яркость свечения

    for (auto& mod : gFeatureManager->mModuleManager->getModules()) {
        if (!mod->isEnabled()) continue;

        std::string name = mod->getName();
        std::string mode = mod->getMode();
        std::string fullText = name + (mode.empty() ? "" : " " + mode);
        ImVec2 textSize = ImGui::CalcTextSize(fullText.c_str());

        ImVec2 pos = ImVec2(startPos.x - textSize.x, startPos.y);

        ImU32 nameColor = ColorUtils::getThemedColor(0);
        ImU32 modeColor = IM_COL32(180, 180, 180, 255);
        ImU32 glowColor = ColorUtils::getThemedColor(1);

        // Обработка анимации исчезновения
        float fadeAlpha = mFadeProgress;  // Используем значение прозрачности
        if (fadeAlpha < 1.0f) {
            fadeAlpha = fadeAlpha * 0.8f;  // Плавное уменьшение прозрачности (к примеру, за несколько кадров)
        }

        // Фон с размытием
        ImVec2 bgStart = ImVec2(pos.x - 5, pos.y - 2);
        ImVec2 bgEnd = ImVec2(startPos.x + 5, pos.y + textSize.y + 2);
        drawList->AddRectFilled(bgStart, bgEnd, IM_COL32(0, 0, 0, 100), 5.0f);

        // Отрисовка текста с учетом прозрачности
        drawList->AddText(ImVec2(pos.x, pos.y), IM_COL32(255, 255, 255, (int)(255 * fadeAlpha)), name.c_str());
        if (!mode.empty()) {
            drawList->AddText(ImVec2(pos.x + ImGui::CalcTextSize(name.c_str()).x, pos.y), modeColor, mode.c_str());
        }

        // Обработка режимов отображения
        switch (mMode.getEnum()) {
            case Mode::None:
                break;
            case Mode::Split:
                drawList->AddLine(ImVec2(bgStart.x, bgEnd.y), ImVec2(bgEnd.x, bgEnd.y), modeColor, 1.5f);
                break;
            case Mode::Bar:
                drawList->AddRectFilled(ImVec2(bgStart.x, bgEnd.y), ImVec2(bgEnd.x, bgEnd.y + 3), glowColor, 3.0f);
                break;
        }

        startPos.y += textSize.y + 5;
    }
}