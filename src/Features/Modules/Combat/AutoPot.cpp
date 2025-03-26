//
// Created by Жена on 21.03.2025.
//

#include "AutoPot.hpp"
#include "Features/Events/BaseTickEvent.hpp"
#include "SDK/Minecraft/ClientInstance.hpp"
#include "SDK/Minecraft/Actor/Actor.hpp"
#include "SDK/Minecraft/Inventory/PlayerInventory.hpp"
#include "SDK/Minecraft/Inventory/Item.hpp"
#include <FeatureManager.hpp>

void AutoPot::onEnable() {
    gFeatureManager->mDispatcher->listen<BaseTickEvent, &AutoPot::onBaseTickEvent>(this);
}

void AutoPot::onDisable() {
    gFeatureManager->mDispatcher->deafen<BaseTickEvent, &AutoPot::onBaseTickEvent>(this);
}

void AutoPot::onBaseTickEvent(BaseTickEvent& event) {
    auto player = ClientInstance::get()->getLocalPlayer();
    if (!player || player->isDead()) return;

    float currentHealth = player->getHealth();
    float maxHealth = player->getMaxHealth();

    // Если здоровье ниже 60% от максимального — используем суп
    if (currentHealth <= maxHealth * 0.6f) {
        useSoup();
    }
}

void AutoPot::useSoup() {
    auto player = ClientInstance::get()->getLocalPlayer();
    if (!player) return;

    auto inventory = player->getInventory();
    if (!inventory) return;

    for (int slot = 0; slot < inventory->getSize(); slot++) {
        auto item = inventory->getItem(slot);
        if (!item.isValid()) continue;

        // Проверяем, является ли предмет грибным супом
        if (item.getID() == Item::MushroomStew) {
            player->setSelectedSlot(slot);
            player->useItem();
            break; // Остановить после использования первого супа
        }
    }
}