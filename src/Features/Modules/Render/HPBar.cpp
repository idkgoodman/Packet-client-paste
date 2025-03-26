//
// Created by Жена on 21.03.2025.
//

#include "Features/Modules/Render/HPBar.hpp"
#include "Features/Events/RenderEvent.hpp"
#include "SDK/Minecraft/MinecraftGame.hpp"
#include "SDK/Minecraft/ClientInstance.hpp"
#include "Utils/MiscUtils/ImRenderUtils.hpp"
#include "imgui.h"
#include "Features/FeatureManager.hpp"
#include "SDK/Minecraft/Actor/Actor.hpp"

void HPBar::onEnable()
{
    gFeatureManager->mDispatcher->listen<RenderEvent, &HPBar::onRenderEvent>(this);
}

void HPBar::onDisable()
{
    gFeatureManager->mDispatcher->deafen<RenderEvent, &HPBar::onRenderEvent>(this);
}

void HPBar::onRenderEvent(RenderEvent& event) {
    auto drawList = ImGui::GetForegroundDrawList();
    ImVec2 pos = mElement->getPos();
    ImVec2 size = mElement->mSize;

    float maxHealth = 20.0f; // Ванильное макс. здоровье
    float health = MinecraftGame::getPlayer()->getHealth();
    float absorption = MinecraftGame::getPlayer()->getAbsorptionAmount();
    float healthPercent = std::min(health / maxHealth, 1.0f);
    float absorptionPercent = std::min(absorption / maxHealth, 1.0f);

    // Фон с размытием
    ImVec4 area = ImVec4(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
    ImRenderUtils::addBlur(area, 6.f, 6.f, drawList, false);

    // Тени
    drawList->AddShadowRect(ImVec2(pos.x - 3, pos.y - 3), ImVec2(area.z + 3, area.w + 3), ImColor(0.f, 0.f, 0.f, 1.f), 50.f, ImVec2(0, 0));

    // Полоска здоровья
    drawList->AddRectFilled(pos, ImVec2(pos.x + size.x * healthPercent, pos.y + size.y), IM_COL32(255, 0, 0, 255), 5.0f);

    // Полоска золотых сердец (если есть)
    if (absorption > 0) {
        drawList->AddRectFilled(ImVec2(pos.x + size.x * healthPercent, pos.y),
                                ImVec2(pos.x + size.x * (healthPercent + absorptionPercent), pos.y + size.y),
                                IM_COL32(255, 165, 0, 255), 5.0f);
    }
}