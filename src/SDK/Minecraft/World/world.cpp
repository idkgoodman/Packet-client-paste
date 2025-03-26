//
// Created by Жена on 23.03.2025.
//

#include "world.hpp"

World::World()
    : currentWeather(Weather::Rain), currentTimeOfDay(TimeOfDay::Day), customTime(1000), cloudsEnabled(true) {}

void World::setWeather(Weather weather) {
    currentWeather = weather;
}

void World::setTimeOfDay(TimeOfDay timeOfDay) {
    currentTimeOfDay = timeOfDay;
}

void World::setCustomTime(int time) {
    customTime = time;
}

void World::enableClouds(bool enable) {
    cloudsEnabled = enable;
}

Weather World::getWeather() const {
    return currentWeather;
}

TimeOfDay World::getTimeOfDay() const {
    return currentTimeOfDay;
}

int World::getCustomTime() const {
    return customTime;
}

bool World::areCloudsEnabled() const {
    return cloudsEnabled;
}
