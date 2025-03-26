//
// Created by Жена on 23.03.2025.
//

#include <vector>
#include "GuiData.hpp"
#include "ColorUtils.hpp"
#include <keyHook.hpp>

struct KeyState {
    bool pressed;
    float fillAmount; // 0.0 - нет заливки, 1.0 - полная заливка
};

std::map<int, KeyState> keyStates = {
    { 'W', {false, 0.0f} },
    { 'A', {false, 0.0f} },
    { 'S', {false, 0.0f} },
    { 'D', {false, 0.0f} },
    { VK_SPACE, {false, 0.0f} }
};

void RenderKeystrokes() {
    auto themeColor = ColorUtils::GetThemedColor(0);
    auto blurColor = Color(100, 100, 100, 150); // Серый цвет размытия

    for (auto& [key, state] : keyStates) {
        bool isPressed = KeyHook::IsKeyDown(key);

        // Анимация заполнения (плавное изменение)
        if (isPressed) {
            state.fillAmount += 0.1f;
            if (state.fillAmount > 1.0f) state.fillAmount = 1.0f;
        } else {
            state.fillAmount -= 0.1f;
            if (state.fillAmount < 0.0f) state.fillAmount = 0.0f;
        }

        Color keyColor = (key == VK_SPACE) ? themeColor : themeColor;

        // Рисуем кнопку с эффектом размытия внутри
        GuiData::DrawKey(key, keyColor, blurColor, state.fillAmount);
    }
}