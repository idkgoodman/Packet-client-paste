
#pragma once

#include "Packet.hpp"  // ���� � ��� ���� ����� ����� ��� �������

class CriticalHitPacket : public Packet {
public:
    int entityId;    // ID ��������, �� ������� ��� ������ ����
    bool isCritical; // ����, �����������, ��� ���� �����������

    CriticalHitPacket(int entityId, bool isCritical)
        : entityId(entityId), isCritical(isCritical) {
    }

    // ����� ��� �������� ������ �� ������ (������)
    void sendPacket(CriticalHitPacket* packet) {
        sendToServer(packet);  // ���������� ����� �� ������
    }

    void applyCritical() {
        CriticalHitPacket packet(entityId, true);  // ������ ������ ������
        sendPacket(&packet);  // ������� ��������� �� ������ ������
    }