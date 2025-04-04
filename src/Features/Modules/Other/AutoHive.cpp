#include "AutoHive.hpp"
#include "CommandUtils.hpp"  // Для отправки команд

// Реализация функции отправки команды
void AutoHive::sendAutoJoinCommand(GameMode selectedGameMode, PlayerCount selectedPlayerCount) {
    std::string modeCommand;

    // Формируем команду в зависимости от выбранного режима
    switch (selectedGameMode) {
        case GameMode::SkyWars:
            modeCommand = "/q skywars-";
        break;
        case GameMode::BedWars:
            modeCommand = "/q bedwars-";
        break;
    }

    // Формируем команду в зависимости от выбранного количества игроков
    switch (selectedPlayerCount) {
        case PlayerCount::Solo:
            modeCommand += "solo";
        break;
        case PlayerCount::Squads:
            modeCommand += "squads";
        break;
        case PlayerCount::Duos:
            modeCommand += "duos";  // Привел к единообразию с маленькими буквами
        break;

    // Отправляем команду в чат
    CommandUtils::sendChatMessage(modeCommand);
}