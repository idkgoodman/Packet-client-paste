//
// Created by Жена on 24.03.2025.
//

#include "BabyBoy.hpp"
#include <ClientInstance.hpp>
#include <ModuleManager.hpp>
#include <Player.hpp>
#include <BaseTickEvent.hpp>
#include <FeatureManager.hpp>

void BabyBoy::onEnable() {
    // Подключаем обработчик событий для тиков
    gFeatureManager->mDispatcher->listen<BaseTickEvent, &BabyBoy::onBaseTickEvent>(this);

    // Уменьшаем рост игрока, применяя коэффициент масштаба
    updateScale();
}

void BabyBoy::onDisable() {
    // Убираем обработчик событий, когда модуль отключен
    gFeatureManager->mDispatcher->deafen<BaseTickEvent, &BabyBoy::onBaseTickEvent>(this);

    // Восстанавливаем нормальный размер игрока
    resetScale();
}

void BabyBoy::onBaseTickEvent(BaseTickEvent& event) {
    // Получаем игрока
    auto* player = gClientInstance->getLocalPlayer();
    if (!player) return;

    // Если модуль включен, изменяем рост
    if (isEnabled) {
        updateScale();
    }
}

void BabyBoy::updateScale() {
    // Получаем игрока и применяем уменьшение по оси Y
    auto* player = gClientInstance->getLocalPlayer();
    if (player) {
        player->setScale(1.0f, scaleFactor, 1.0f); // scaleFactor - это переменная для изменения высоты
    }
}

void BabyBoy::resetScale() {
    // Возвращаем нормальный масштаб игрока
    auto* player = gClientInstance->getLocalPlayer();
    if (player) {
        player->setScale(1.0f, 1.0f, 1.0f); // Возвращаем стандартный масштаб
    }
}