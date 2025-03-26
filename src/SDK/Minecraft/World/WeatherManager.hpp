//
// Created by Жена on 23.03.2025.
//

#ifndef WEATHERMANAGER_HPP
#define WEATHERMANAGER_HPP

#include <string>

class WeatherManager {
public:
    // Типы погодных условий
    enum class Weather {
        Thunderstorm,
        Rain,
        Snow,
        None
    };

    // Типы времени суток
    enum class Time {
        Day,
        Night,
        Sunset,
        Morning,
        Custom
    };

    // Конструктор
    WeatherManager();

    // Функции для управления погодой
    void setWeather(Weather weather);
    Weather getCurrentWeather() const;

    // Функции для управления временем
    void setTime(Time time);
    void setCustomTime(int hours, int minutes);
    Time getCurrentTime() const;

    // Функция для управления облаками
    void enableClouds(bool enable);

private:
    Weather currentWeather;
    Time currentTime;
    int customTimeHours;
    int customTimeMinutes;
    bool cloudsEnabled;
};

#endif //WEATHERMANAGER_HPP
