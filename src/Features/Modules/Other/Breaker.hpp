#pragma once

#include <Actor.hpp>
#include <FeatureManager.hpp>
#include <Module.hpp>
#include <string>
#include <vector>

#include "Features/Events/BaseTickEvent.hpp"
#include "glm/glm.hpp"
#include "SDK/Minecraft/ClientInstance.hpp"
#include "SDK/Minecraft/Player.hpp"

class Breaker : public ModuleBase<Breaker> {
public:
    // Конструктор для Breaker, задающий начальную дистанцию и угол ротации
    Breaker() : ModuleBase("Breaker", "Breaks beds and lootboxes in range", ModuleCategory::Other, 0, false) {
        addSetting(&mDistance);  // Добавление настройки дистанции
        addSetting(&mRotation);  // Добавление настройки ротации
        mNames = {
            {Lowercase, "breaker"},
            {LowercaseSpaced, "breaker"},
            {Normal, "Breaker"},
            {NormalSpaced, "Breaker"},
        };
    }

    // Метод для включения модуля
    void onEnable() override;

    // Метод для выключения модуля
    void onDisable() override;

    // Событие для проверки блоков каждый тик
    void onBaseTickEvent(BaseTickEvent& event);

private:
    // Настройки модуля
    NumberSetting mDistance = NumberSetting("Distance", "The maximum distance to break blocks", 10.0f, 1.0f, 50.0f);
    NumberSetting mRotation = NumberSetting("Rotation", "The rotation angle for the player before breaking blocks", 0.0f, 0.0f, 360.0f);

    // Метод для разрушения блока по ID
    void breakBlock(const std::string& blockID);

    // Метод для поиска ближайших блоков
    std::vector<std::string> findNearbyBlocks();

    // Метод для разрушения блока кровати или лутбокса в пределах заданной дистанции
    void checkAndBreakBlocks();

    // Приватная переменная для хранения состояния модуля
    bool isActive = false;

    // Метод для установки ротации игрока
    void setRotation(float angle);
};
