//
// Created by Жена on 23.03.2025.
//

#ifndef WORLD_HPP
#define WORLD_HPP

#pragma once

#include <string>

// Перечисление для погодных условий
enum class Weather {
    Thunderstorm,
    Rain,
    Snow
};

// Перечисление для времени суток
enum class TimeOfDay {
    Day,
    Night,
    Sunset,
    Morning
};

class World {
public:
    World();

    // Настройки для погоды и времени
    void setWeather(Weather weather);
    void setTimeOfDay(TimeOfDay timeOfDay);
    void setCustomTime(int time);
    void enableClouds(bool enable);

    Weather getWeather() const;
    TimeOfDay getTimeOfDay() const;
    int getCustomTime() const;
    bool areCloudsEnabled() const;

private:
    Weather currentWeather;
    TimeOfDay currentTimeOfDay;
    int customTime;
    bool cloudsEnabled;
};

#endif //WORLD_HPP
