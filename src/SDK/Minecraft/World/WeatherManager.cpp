//
// Created by Жена on 23.03.2025.
//

#include "WeatherManager.hpp"

WeatherManager::WeatherManager()
    : currentWeather(Weather::None), currentTime(Time::Day),
      customTimeHours(12), customTimeMinutes(0), cloudsEnabled(true) {}

void WeatherManager::setWeather(Weather weather) {
    currentWeather = weather;
    // Логика для изменения погоды в Minecraft
    switch (weather) {
        case Weather::Thunderstorm:
            // Установить грозу
                break;
        case Weather::Rain:
            // Установить дождь
                break;
        case Weather::Snow:
            // Установить снег
                break;
        case Weather::None:
            // Убрать погоду
                break;
    }
}

WeatherManager::Weather WeatherManager::getCurrentWeather() const {
    return currentWeather;
}

void WeatherManager::setTime(Time time) {
    currentTime = time;
    // Логика для изменения времени суток в Minecraft
    switch (time) {
        case Time::Day:
            // Установить день
                break;
        case Time::Night:
            // Установить ночь
                break;
        case Time::Sunset:
            // Установить закат
                break;
        case Time::Morning:
            // Установить утро
                break;
        case Time::Custom:
            // Установить кастомное время
                break;
    }
}

void WeatherManager::setCustomTime(int hours, int minutes) {
    customTimeHours = hours;
    customTimeMinutes = minutes;
    // Логика для изменения времени на кастомное
}

WeatherManager::Time WeatherManager::getCurrentTime() const {
    return currentTime;
}

void WeatherManager::enableClouds(bool enable) {
    cloudsEnabled = enable;
    // Логика для включения/выключения облаков
}
