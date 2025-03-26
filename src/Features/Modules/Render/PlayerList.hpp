#ifndef PLAYERLIST_HPP
#define PLAYERLIST_HPP

#include <vector>
#include <string>
#include "Actor.hpp"  // Предполагается, что у тебя есть класс Actor
#include "Features/Events/RenderEvent.hpp"
#include "Features/Events/BaseTickEvent.hpp"

class PlayerList {
public:
    // Конструктор и деструктор
    PlayerList();
    ~PlayerList();

    // Методы для работы с актерами
    void updatePlayerList();  // Обновление списка актеров
    void togglePlayerList();  // Переключение видимости списка актеров

    // Методы для обработки событий
    void onEnable();  // Включить модуль
    void onDisable(); // Отключить модуль

    void onRenderEvent(RenderEvent& event);  // Обработчик рендера
    void onBaseTickEvent(BaseTickEvent& event);  // Обработчик события тикания

    // Обработчик нажатия клавиши Tab
    void onTick();

private:
    // Список актеров
    std::vector<Actor> actors;

    // Флаг для отображения списка
    bool showPlayerList = false;

    // Флаг для проверки нажатия клавиши Tab
    bool isTabPressed = false;

    // Получить реальный IP сервера
    std::string getServerIP();
};

#endif // PLAYERLIST_HPP