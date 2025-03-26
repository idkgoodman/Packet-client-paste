#pragma once

#include "Features/Modules/Visual/ParticleEffect.hpp"
#include "Features/Events/RenderEvent.hpp"
#include "Features/Events/BaseTickEvent.hpp"
#include "Features/Events/AttackEvent.hpp" // Подключаем событие атаки
#include "imgui.h"
#include "glm/glm.hpp"
#include <string>

class HitEffects : public ModuleBase<HitEffects> {
public:
    HitEffects() : ModuleBase<HitEffects>("HitEffects", "Effects to your hits", ModuleCategory::Visual, 0, false) {
        mNames = {
            {Lowercase, "hiteffects"},
            {LowercaseSpaced, "hit effects"},
            {Normal, "HitEffects"},
            {NormalSpaced, "Hit Effects"}
        };
    }

    void onEnable() override {
        // Подписываемся на события атак
        gFeatureManager->mDispatcher->listen<AttackEvent, &HitEffects::onAttackEvent>(this);
    }

    void onDisable() override {
        // Отписываемся от события атак
        gFeatureManager->mDispatcher->deafen<AttackEvent, &HitEffects::onAttackEvent>(this);
    }

    // Обработчик события атаки
    void onAttackEvent(AttackEvent& event) {
        glm::vec3 attackPosition = event.getAttackPosition();  // Позиция удара
        bool isCritical = event.isCriticalHit();  // Проверка на критический удар

        if (isCritical) {
            ParticleEffect::addEffect(attackPosition, ParticleEffect::Type::CriticalHit);
        } else {
            // Выбираем тип удара (меч или обычный)
            if (event.isWeaponUsed("sword")) {
                ParticleEffect::addEffect(attackPosition, ParticleEffect::Type::SwordHit);
            } else {
                ParticleEffect::addEffect(attackPosition, ParticleEffect::Type::RegularHit);
            }
        }
    }
