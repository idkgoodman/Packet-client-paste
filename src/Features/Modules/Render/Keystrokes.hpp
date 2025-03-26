//
// Created by Жена on 23.03.2025.
//

#ifndef KEYSTROKES_HPP
#define KEYSTROKES_HPP

#pragma once

#include <string>
#include <imgui.h>
#include "Module.hpp"
#include "ColorUtils.hpp"

class Keystrokes : public ModuleBase<Keystrokes> {
public:
    enum Key { W, A, S, D, Space };

    mNames = {
        {Lowercase, "keystrokes"},
        {LowercaseSpaced, "keystrokes"},
        {Normal, "Keystrokes"},
        {NormalSpaced, "Keystrokes"},
    };
}


    // Позиция модуля в интерфейсе
    float mPosX = 100.0f;
    float mPosY = 100.0f;

    // Функция для отображения модуля на экране
    void render() {
        // Отображаем кнопки WASD и пробел
        ImGui::SetCursorPos(ImVec2(mPosX, mPosY));

        // Цвет кнопок по теме
        auto keyColor = ColorUtils::GetThemedColor(0);

        // Отображаем клавиши WASD и пробел
        ImGui::TextColored(keyColor, "W");
        ImGui::SameLine();
        ImGui::TextColored(keyColor, "A");
        ImGui::SameLine();
        ImGui::TextColored(keyColor, "S");
        ImGui::SameLine();
        ImGui::TextColored(keyColor, "D");
        ImGui::SameLine();
        ImGui::TextColored(keyColor, "Space");
    }

    // Функция для перемещения модуля с помощью HUD Editor
    void move(float deltaX, float deltaY) {
        mPosX += deltaX;
        mPosY += deltaY;
    }

    // Функция для отображения настроек в HUD Editor
    void showEditorSettings() {
        // Здесь можно добавить настройки для позиционирования
        if (ImGui::Begin("Keystrokes Settings")) {
            ImGui::SliderFloat("Position X", &mPosX, 0.0f, 1920.0f);
            ImGui::SliderFloat("Position Y", &mPosY, 0.0f, 1080.0f);
            ImGui::End();
        }
    }

    Keystrokes() : ModuleBase("Keystrokes", "Displays WASD keys and spacebar", ModuleCategory::Render, 0, false) {
        // Добавляем настройки для перемещения
        addSettings(
            // Можно добавить дополнительные настройки сюда
        );
    }
};

#endif //KEYSTROKES_HPP
