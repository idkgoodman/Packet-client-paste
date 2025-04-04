
#pragma once

#include "Packet.hpp"  // Если у вас есть общий класс для пакетов

class CriticalHitPacket : public Packet {
public:
    int entityId;    // ID сущности, на которую был нанесён удар
    bool isCritical; // Флаг, указывающий, что удар критический

    CriticalHitPacket(int entityId, bool isCritical)
        : entityId(entityId), isCritical(isCritical) {
    }

    // Метод для отправки пакета на сервер (пример)
    void sendPacket(CriticalHitPacket* packet) {
        sendToServer(packet);  // Отправляем пакет на сервер
    }

    void applyCritical() {
        CriticalHitPacket packet(entityId, true);  // Создаём объект пакета
        sendPacket(&packet);  // Передаём указатель на объект пакета
    }