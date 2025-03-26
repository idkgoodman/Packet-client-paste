#pragma once

#include <string>
#include <Module.hpp>
#include <Utils/ColorUtils.hpp>
#include <SDK/Minecraft/Actor/Actor.hpp>
#include <SDK/Minecraft/ClientInstance.hpp>
#include <SDK/Minecraft/Actor/Components/MoveInputComponent.hpp>

class Nametags : public ModuleBase<Nametags> {
public:
    Nametags() : ModuleBase("Nametags", "Display player names with styled tags", ModuleCategory::Render) {}

    void renderNametag(Actor* actor) {
        if (!actor) return;

        auto playerName = actor->getName();
        if (playerName.empty()) return;

        // Calculate the position for the name tag (above the player's head)
        auto pos = actor->getPosition();
        pos.y += 2.0f; // Slightly above the player's head

        // Set up drawing parameters
        ImVec2 nameTagPos = ImVec2(pos.x, pos.y);
        ImVec2 nameTagSize = ImVec2(100, 30); // Fixed size for name tag

        // Draw background rectangle with rounded corners and blur
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        drawList->AddRectFilled(nameTagPos, ImVec2(nameTagPos.x + nameTagSize.x, nameTagPos.y + nameTagSize.y), ImColor(0, 0, 0, 180)); // Background
        drawList->AddRect(nameTagPos, ImVec2(nameTagPos.x + nameTagSize.x, nameTagPos.y + nameTagSize.y), ImColor(255, 255, 255, 255)); // Border

        // Display the player name
        ImGui::SetCursorScreenPos(nameTagPos);
        ImGui::Text(playerName.c_str());

        // Add glow effect or other visual tweaks if needed (optional)
    }

    void onTick() {
        auto player = ClientInstance::get()->getLocalPlayer();
        if (!player) return;

        for (auto& actor : ClientInstance::get()->getWorld()->getActors()) {
            if (actor != player) {
                renderNametag(actor);
            }
        }
    }
};