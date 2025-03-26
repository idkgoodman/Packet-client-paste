//
// Created by Жена on 23.03.2025.
//

#include "Ambience.hpp"
#include "WeatherManager.hpp"
#include <iostream>

// Функция для изменения погоды
void Ambience::setWeather(WeatherManager::Weather weather) {
    weatherManager.setWeather(weather); // Устанавливаем погоду через WeatherManager
}

// Функция для изменения времени суток
void Ambience::setTime(WeatherManager::Time time) {
    weatherManager.setTime(time); // Устанавливаем время суток через WeatherManager
}

// Функция для установки кастомного времени
void Ambience::setCustomTime(int hours, int minutes) {
    weatherManager.setCustomTime(hours, minutes); // Устанавливаем кастомное время
}

// Функция для включения/выключения облаков
void Ambience::enableClouds(bool enable) {
    weatherManager.setClouds(enable); // Включаем или выключаем облака через WeatherManager
}

// Функции для получения текущих настроек
WeatherManager::Weather Ambience::getCurrentWeather() const {
    return weatherManager.getWeather(); // Получаем текущую погоду через WeatherManager
}

WeatherManager::Time Ambience::getCurrentTime() const {
    return weatherManager.getTime(); // Получаем текущее время суток через WeatherManager
}

// Функция для отображения текущих настроек
void Ambience::displaySettings() const {
    std::cout << "Weather: " << static_cast<int>(getCurrentWeather()) << "\n";
    std::cout << "Time: " << static_cast<int>(getCurrentTime()) << "\n";
    std::cout << "Clouds: " << (mClouds.mValue ? "Enabled" : "Disabled") << "\n";
    if (mCustomTime.mValue) {
        std::cout << "Custom Time: Enabled\n";
    } else {
        std::cout << "Custom Time: Disabled\n";
    }
}