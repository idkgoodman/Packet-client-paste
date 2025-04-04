#include "Criticals.hpp"
#include <CriticalHitPacket.hpp>

// Конструктор модуля
Criticals::Criticals() : ModuleBase("Criticals", "Makes every hit critical", ModuleCategory::Combat, 0, false) {
    mNames = {
        {Lowercase, "criticals"},
        {LowercaseSpaced, "criticals"},
        {Normal, "Criticals"},
        {NormalSpaced, "Criticals"},
    };
}

// onTick вызывается каждый тик игры
void Criticals::onTick() {
    // Логика применения критов в зависимости от выбранного bypass mode
    switch (currentBypassMode) {
    case BypassMode::Packet:
        applyPacketCritical();
        break;
    case BypassMode::Motion:
        applyMotionCritical();
        break;
    case BypassMode::Hybrid:
        applyHybridCritical();
        break;
    }
}

// Применение критического удара через пакеты
void Criticals::onTick() {
    if (getMode() == BypassMode::Packet) {
        applyPacketCritical();  // Отправляем пакет с критическим ударом
    }
}

void Criticals::applyPacketCritical() {
    // Проверяем, что мы в правильном состоянии (например, не находимся в воздухе, чтобы применить критику)
    if (isInAir()) return;  // Предположим, что метод проверяет, не находимся ли мы в воздухе

    CriticalHitPacket packet(entityId, true);  // Создаём пакет для критического удара
    sendPacket(&packet);  // Отправляем пакет
}

void Criticals::onTick() {
    if (getMode() == BypassMode::Motion) {
        applyMotionCritical();  // Применяем критический удар через motion
    }
}

void Criticals::applyMotionCritical() {
    // Проверяем, что игрок не в воздухе и не уже в движении для крита
    if (isInAir()) return;  // Предположим, что метод проверяет, не находимся ли мы в воздухе

    // Здесь мы изменяем скорость игрока или его вектор движения
    Vector3f velocity = getVelocity();  // Получаем текущую скорость игрока
    velocity.y += 0.42f;  // Параметр для подъема вверх (имитирует прыжок для крита)

    setVelocity(velocity);  // Устанавливаем новую скорость для игрока, чтобы имитировать критический удар
}
// Применение комбинированного критического удара (Packet + Motion)
void Criticals::applyHybridCritical() {
    applyPacketCritical();
    applyMotionCritical();
}
