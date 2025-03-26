#include "Breaker.hpp"
#include <
#include <cmath>
#include "Logger.hpp"
#include "SDK/Minecraft/ClientInstance.hpp"
#include "SDK/Minecraft/Player.hpp"

// Включение модуля
void Breaker::onEnable() {
    isActive = true;
    Logger::Info("Breaker module enabled");
}

// Выключение модуля
void Breaker::onDisable() {
    isActive = false;
    Logger::Info("Breaker module disabled");
}

// Основной обработчик событий тика
void Breaker::onBaseTickEvent(BaseTickEvent& event) {
    if (!isActive) return;

    // Получаем список блоков для разрушения
    auto blocks = findNearbyBlocks();

    // Если есть блоки, то проверяем и ломаем их
    if (!blocks.empty()) {
        checkAndBreakBlocks();
    }
}

// Разрушение блока по ID
void Breaker::breakBlock(const std::string& blockID) {
    // Логика разрушения блока (подключение к серверу или локальная логика)
    Logger::Info("Breaking block with ID: %s", blockID.c_str());
}

// Поиск ближайших блоков для разрушения
std::vector<std::string> Breaker::findNearbyBlocks() {
    // Логика поиска блоков в радиусе
    // Здесь мы возвращаем список блоков (например, кровати и лутбоксы)
    return {"bed", "lootbox"};
}

// Проверка и разрушение блоков в пределах заданной дистанции
void Breaker::checkAndBreakBlocks() {
    // Проверяем все найденные блоки
    for (const auto& block : findNearbyBlocks()) {
        // Поворот игрока перед разрушением блока
        setRotation(mRotation.getValue());

        // Разрушаем блок
        breakBlock(block);
    }
}

// Установка ротации игрока
void Breaker::setRotation(float angle) {
    // Преобразуем угол в радианы
    float radians = glm::radians(angle);

    // Логика установки ротации игрока
    Player* player = ClientInstance::getLocalPlayer();
    if (player) {
        player->setYaw(radians);
        player->setPitch(radians);
        Logger::Info("Setting rotation to: %f degrees", angle);
    }
}