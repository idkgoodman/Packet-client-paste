#pragma once

#include <Features/Modules/Module.hpp>
#include <Features/Modules/Setting.hpp>

class Criticals : public ModuleBase<Criticals> {
public:
    enum class Mode {
        Vanilla,
    };

    enum class BypassMode {
        Packet,
        Motion,
        Hybrid
    };

    enum class AnimationState {
        START,
        MID_AIR,
        MID_AIR2,
        LANDING,
        FINISHED
    };

    Criticals();  // Конструктор модуля
    void onTick() override;  // Метод, который будет вызываться каждый тик игры

private:
    void applyCritical();  // Метод для применения критического удара
    void applyPacketCritical();  // Метод для обработки критов через пакеты
    void applyMotionCritical();  // Метод для обработки критов через движение
    void applyHybridCritical();  // Метод для комбинированного критового удара
};
