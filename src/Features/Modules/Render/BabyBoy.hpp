//
// Created by Жена on 24.03.2025.
//
#ifndef BABYBOY_HPP
#define BABYBOY_HPP

#include <Module.hpp>
#include <FeatureManager.hpp>
#include <BaseTickEvent.hpp>
#include <Actor.hpp>

class BabyBoy : public ModuleBase<BabyBoy> {
public:
    BabyBoy()
        : ModuleBase<BabyBoy>("BabyBoy", "Reduces the player's height", ModuleCategory::Render) {

        mNames = {
            {Lowercase, "babyboy"},
            {LowercaseSpaced, "baby boy"},
            {Normal, "BabyBoy"},
            {NormalSpaced, "Baby Boy"}
        };
    }

    // Функции, которые будут вызваны при включении и выключении модуля
    void onEnable() override;
    void onDisable() override;

    // Событие для тиковой обработки, будет вызываться каждый тик
    void onBaseTickEvent(BaseTickEvent& event);

private:
    float scaleFactor = 0.8f;  // Множитель для уменьшения роста (80% от оригинала)
};

#endif // BABYBOY_HPP