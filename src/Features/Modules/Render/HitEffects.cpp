#include "Features/Modules/Visual/ParticleEffect.hpp"
#include "Features/Events/RenderEvent.hpp"
#include "Features/Events/BaseTickEvent.hpp"
#include "Features/Events/AttackEvent.hpp" // Здесь представим, что есть событие атаки
#include "imgui.h"
#include "glm/glm.hpp"
#include <string>
#include "HitEffects.hpp"

void HitEffects::onEnable()
{
    gFeatureManager->mDispatcher->listen<RenderEvent, &HitEffects::onRenderEvent>(this);
}

void HitEffects::onDisable()
{
    gFeatureManager->mDispatcher->deafen<RenderEvent, &HitEffects::onRenderEvent>(this);
}

// Для упрощения добавим базовый класс эффекта
class ParticleEffect {
public:
    enum class Type {
        CriticalHit,  // Критический удар
        SwordHit,     // Удар мечом
        RegularHit    // Обычный удар
    };

    static void addEffect(const glm::vec3& position, Type type) {
        // Здесь мы генерируем партикль, который будет отрисован
        switch (type) {
        case Type::CriticalHit:
            // Генерация эффекта критического удара
            // В реальности тут будет добавление анимации партиклей
            std::cout << "Critical hit effect at: " << position.x << ", " << position.y << ", " << position.z << std::endl;
            break;
        case Type::SwordHit:
            // Генерация эффекта удара мечом
            std::cout << "Sword hit effect at: " << position.x << ", " << position.y << ", " << position.z << std::endl;
            break;
        case Type::RegularHit:
            // Генерация эффекта обычного удара
            std::cout << "Regular hit effect at: " << position.x << ", " << position.y << ", " << position.z << std::endl;
            break;
        }
    }
};

class LevelInfo : public ModuleBase<LevelInfo> {
public:
    LevelInfo() : ModuleBase("LevelInfo", "Displays FPS, BPS, or CPS", ModuleCategory::Visual, 0, false) {
        // Инициализация необходимых данных и HUD
    }

    void onEnable() override {
        // Подключаем обработчик событий атаки и отрисовки
        gFeatureManager->mDispatcher->listen<RenderEvent, &LevelInfo::onRenderEvent>(this);
        gFeatureManager->mDispatcher->listen<BaseTickEvent, &LevelInfo::onBaseTickEvent>(this);
        gFeatureManager->mDispatcher->listen<AttackEvent, &LevelInfo::onAttackEvent>(this); // Подписка на событие атаки
    }

    void onDisable() override {
        gFeatureManager->mDispatcher->deafen<RenderEvent, &LevelInfo::onRenderEvent>(this);
        gFeatureManager->mDispatcher->deafen<BaseTickEvent, &LevelInfo::onBaseTickEvent>(this);
        gFeatureManager->mDispatcher->deafen<AttackEvent, &LevelInfo::onAttackEvent>(this); // Отписка от события атаки
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
