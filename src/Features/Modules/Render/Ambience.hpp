#pragma once

#ifndef AMBIENCE_HPP
#define AMBIENCE_HPP

#include <string>
#include "WeatherManager.hpp"
#include <Module.hpp>

class Ambience : public ModuleBase<Ambience> {
public:
    enum class Weather {
        ThunderStorm,
        Rain,
        Snow,
        None
    };

    enum class Time {
         Day,
         Night,
         Sunset,
         Morning
    };

    // Настройки
    EnumSetting<Weather> mWeather = EnumSettingT("Weather", "What Weather should it be like", Weather::None, "ThunderStorm", "Rain", "Snow", "Morning");
    EnumSetting<Time> mTime = EnumSettingT("Time", "What Time should it be like", Time::Day, "Day", "Night", "Morning", "Sunset");
    BoolSetting mCustomTime = BoolSetting("Custom Time", "Whether or not use Custom Time", false);
    BoolSetting mClouds = BoolSetting("Clouds", "Whether or not show Clouds in the sky", true);

    Ambience() : ModuleBase("Ambience", "Choose your weather, clouds, and time!", ModuleCategory::Render, 0, false) {
        addSettings(
            &mWeather,
            &mClouds,
            &mTime,
            &mCustomTime
        );

        // Условие видимости настроек
        VISIBILITY_CONDITION(mCustomTime, mClouds.mValue);
        VISIBILITY_CONDITION(mWeather, mTime.mValue);

        mNames = {
            {Lowercase, "ambience"},
            {LowercaseSpaced, "ambience"},
            {Normal, "Ambience"},
            {NormalSpaced, "Ambience"},
        };
    }

    // Функция для изменения погоды
    void setWeather(WeatherManager::Weather weather) {
        weatherManager.setWeather(weather); // Вызов функции управления погодой в WeatherManager
    }

    // Функция для изменения времени суток
    void setTime(WeatherManager::Time time) {
        weatherManager.setTime(time); // Вызов функции управления временем в WeatherManager
    }

    // Функция для установки кастомного времени
    void setCustomTime(int hours, int minutes) {
        weatherManager.setCustomTime(hours, minutes); // Установка кастомного времени через WeatherManager
    }

    // Функция для включения/выключения облаков
    void enableClouds(bool enable) {
        weatherManager.setClouds(enable); // Управление облаками через WeatherManager
    }

    // Функции для получения текущих настроек
    WeatherManager::Weather getCurrentWeather() const {
        return weatherManager.getWeather(); // Получение текущей погоды через WeatherManager
    }

    WeatherManager::Time getCurrentTime() const {
        return weatherManager.getTime(); // Получение текущего времени через WeatherManager
    }

    // Функция для отображения текущих настроек
    void displaySettings() const {
        // Печать текущих настроек (для отладки)
        std::cout << "Weather: " << static_cast<int>(getCurrentWeather()) << "\n";
        std::cout << "Time: " << static_cast<int>(getCurrentTime()) << "\n";
        std::cout << "Clouds: " << (mClouds.mValue ? "Enabled" : "Disabled") << "\n";
        if (mCustomTime.mValue) {
            std::cout << "Custom Time: Enabled\n";
        } else {
            std::cout << "Custom Time: Disabled\n";
        }
    }

private:
    WeatherManager weatherManager; // Менеджер для работы с погодой и временем
};

#endif // AMBIENCE_HPP