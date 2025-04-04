#ifndef AUTOHIVE_HPP
#define AUTOHIVE_HPP

// AutoHive.hpp
#pragma once

#include <string>
#include <Module.hpp>

class AutoHive : public ModuleBase<AutoHive> {
public:
    enum class GameMode {
        SkyWars,
        BedWars
    };

    enum class PlayerCount {
        Solo,
        Squads,
        Duos
    };

    // Настройки для выбора режима и количества игроков
    EnumSettingT mGameMode = EnumSettingT("Game Mode", "What game mode to join");
    EnumSettingT mPlayerCount = EnumSettingT("Player Count", "How many players should be in one team");

    // Конструктор
    AutoHive() : ModuleBase<AutoHive>("AutoHive", "Join on Modes on hive", ModuleCategory::Other, 0, false) {
        addSetting(&mGameMode);
        addSetting(&mPlayerCount);

        // Условие видимости
        VISIBILITY_CONDITION(mGameMode, mPlayerCount.mValue);

        // Имена для модуля
        mNames = {
            {Lowercase, "autohive"},
            {LowercaseSpaced, "auto hive"},
            {Normal, "AutoHive"},
            {NormalSpaced, "Auto Hive"},
        };
    }

    // Функция для отправки команды на сервер
    static void sendAutoJoinCommand(GameMode selectedGameMode, PlayerCount selectedPlayerCount);

private:
    std::vector<std::pair<NameType, std::string>> mNames;
};

#endif // AUTOHIVE_HPP