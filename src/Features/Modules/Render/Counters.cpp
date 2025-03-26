#include "Features/Modules/Render/Counters.hpp"
#include "Features/Events/BaseTickEvent.hpp"
#include "Features/Events/RenderEvent.hpp"
#include <imgui.h>                    // Для работы с интерфейсом
#include <glm/glm.hpp>                 // Для работы с векторами
#include <ColorUtils.hpp>
#include <ImRenderUtils.hpp>
#include <FeatureManager.hpp>
#include <Counters.hpp>

void Counters::onEnable() {
    gFeatureManager->mDispatcher->listen<BaseTickEvent, &Counters::onBaseTickEvent>(this);
    gFeatureManager->mDispatcher->listen<RenderEvent, &Counters::onRenderEvent>(this);
}

void Counters::onDisable() {
    gFeatureManager->mDispatcher->deafen<BaseTickEvent, &Counters::onBaseTickEvent>(this);
    gFeatureManager->mDispatcher->deafen<RenderEvent, &Counters::onRenderEvent>(this);
}

void Counters::updateStatistics() {
    // Обновление FPS, BPS или CPS в зависимости от текущего состояния
    if (showFPS) {
        fps = getFPS(); // Получаем FPS
    }
    if (showBPS) {
        bps = getBPS(); // Получаем BPS
    }
    if (showCPS) {
        cps = getCPS(); // Получаем CPS
    }
}

void Counters::toggleStat(int stat) {
    // Переключаем видимость статистик
    if (stat == 0) {
        showFPS = !showFPS;
    } else if (stat == 1) {
        showBPS = !showBPS;
    } else if (stat == 2) {
        showCPS = !showCPS;
    }
}

void Counters::onRenderEvent(RenderEvent& event) {
    auto drawList = ImGui::GetForegroundDrawList();
    ImVec2 pos = mElement->getPos();
    ImVec2 size = mElement->mSize;

    // Добавляем эффект размытия фона
    addBlurEffect(pos, size);

    // Тени вокруг
    drawList->AddShadowRect(ImVec2(pos.x - 3, pos.y - 3), ImVec2(pos.x + size.x + 3, pos.y + size.y + 3), ImColor(0.f, 0.f, 0.f, 1.f), 50.f, ImVec2(0, 0));

    // Цвет текста (тема)
    ImU32 themedColor = ColorUtils::getThemedColor(0); // Используем цвет из темы
    ImVec2 textPos = ImVec2(pos.x + 10, pos.y + 10);

    // Отображаем только включенные статистики
    std::string statText = "";
    if (showFPS) {
        statText = "FPS " + std::to_string(fps);
        ImRenderUtils::drawShadowText(drawList, statText, textPos, ImColor(255, 255, 255, 255), 20.f, false);
        textPos.y += 25; // Отступ
    }
    if (showBPS) {
        statText = "BPS " + std::to_string(bps);
        ImRenderUtils::drawShadowText(drawList, statText, textPos, ImColor(255, 255, 255, 255), 20.f, false);
        textPos.y += 25; // Отступ
    }
    if (showCPS) {
        statText = "CPS " + std::to_string(cps);
        ImRenderUtils::drawShadowText(drawList, statText, textPos, ImColor(255, 255, 255, 255), 20.f, false);
        textPos.y += 25; // Отступ
    }
}

void Counters::onBaseTickEvent(BaseTickEvent& event) {
    updateStatistics();
}

void Counters::addBlurEffect(ImVec2 pos, ImVec2 size) {
    // Добавляем размытие фона
    ImVec4 area = ImVec4(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
    ImRenderUtils::addBlur(area, 10.f, 10.f, ImGui::GetForegroundDrawList(), false); // Размытие с увеличенными параметрами
}