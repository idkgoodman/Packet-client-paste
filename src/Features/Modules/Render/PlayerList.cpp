//
// Created by Жена on 21.03.2025.
//

#include "PlayerList.hpp"
#include "Features/Events/RenderEvent.hpp"
#include "Features/Events/BaseTickEvent.hpp"
#include <imgui.h>
#include <SDL2/SDL.h>  // Для работы с клавишами
#include <FeatureManager.hpp>
#include <ImRenderUtils.hpp>
#include <winsock2.h>  // Для получения IP сервера
#pragma comment(lib, "ws2_32.lib")

// Функция для получения IP сервера
std::string getServerIP() {
    WSADATA wsaData;
    char host[256];
    struct hostent *host_info;
    struct in_addr *address;

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    gethostname(host, sizeof(host));
    host_info = gethostbyname(host);
    address = (struct in_addr *)(host_info->h_addr);
    WSACleanup();

    return std::string(inet_ntoa(*address));
}

void PlayerList::updatePlayerList() {
    players.clear();  // Очищаем старый список игроков

    // Получаем список всех игроков
    std::vector<Player> allPlayers = getAllPlayers();  // Пример получения всех игроков

    // Перебираем всех игроков и добавляем в список, если их ID == 63
    for (const auto& player : allPlayers) {
        if (player.id == 63) {
            players.push_back(player);  // Добавляем игрока с ID 63
        }
    }
}

void PlayerList::onRenderEvent(RenderEvent& event) {
    if (!isTabPressed || !showPlayerList) return;

    auto drawList = ImGui::GetForegroundDrawList();
    ImVec2 pos = mElement->getPos();
    ImVec2 size = mElement->mSize;

    // Размытие фона
    ImVec4 area = ImVec4(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
    ImRenderUtils::addBlur(area, 4.f, 4.f, drawList, false);  // Добавляем размытость

    // Тени вокруг
    drawList->AddShadowRect(ImVec2(pos.x - 3, pos.y - 3), ImVec2(area.z + 3, area.w + 3), ImColor(0.f, 0.f, 0.f, 1.f), 50.f, ImVec2(0, 0));

    // Цвета текста
    ImU32 blueColor = ImColor(0.f, 0.f, 1.f, 1.f);  // Голубой цвет
    ImU32 yellowColor = ImColor(1.f, 1.f, 0.f, 1.f);  // Желтый цвет
    ImVec2 textPos = ImVec2(pos.x + 10, pos.y + 10);

    // Отображаем текст "You are playing on " голубым цветом
    std::string playingText = "You are playing on ";
    ImRenderUtils::drawShadowText(drawList, playingText, textPos, blueColor, 20.f, false);
    textPos.y += 25;  // Отступ между строками

    // Получаем реальный IP сервера
    std::string serverIP = getServerIP();

    // Отображаем IP сервера желтым цветом
    ImRenderUtils::drawShadowText(drawList, serverIP, textPos, yellowColor, 20.f, false);
}

void PlayerList::onBaseTickEvent(BaseTickEvent& event) {
    updatePlayerList();  // Обновляем список игроков
}

void PlayerList::onEnable() {
    gFeatureManager->mDispatcher->listen<BaseTickEvent, &PlayerList::onBaseTickEvent>(this);
    gFeatureManager->mDispatcher->listen<RenderEvent, &PlayerList::onRenderEvent>(this);
}

void PlayerList::onDisable() {
    gFeatureManager->mDispatcher->deafen<BaseTickEvent, &PlayerList::onBaseTickEvent>(this);
    gFeatureManager->mDispatcher->deafen<RenderEvent, &PlayerList::onRenderEvent>(this);
}

// Обработчик нажатия клавиши Tab
void PlayerList::onTick() {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    isTabPressed = currentKeyStates[SDL_SCANCODE_TAB];  // Проверяем нажатие клавиши Tab
}