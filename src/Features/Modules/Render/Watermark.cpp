#include "Watermark.hpp"
#include "ColorUtils.hpp"
#include "imgui.h"
#include "Interface.hpp"  // Для доступа к шрифтам из Interface
#include "FontHelper.hpp" // Для работы с шрифтами через FontHelper

// Конструктор модуля
Watermark::Watermark() {
    // Изначальная настройка
    glowEnabled = true;     // Использование подсветки
    boldTextDisabled = false; // Использование жирного текста
    showVersionEnabled = true; // Отображение версии
    showClientDisabled = false; // Отображение клиента
}

// Метод для отображения текста
void Watermark::Render() {
    // Получаем цвет темы
    auto themeColor = ColorUtils::GetThemedColor(0);

    // Получаем шрифты из Interface и FontHelper
    ImFont* regularFont = Interface::GetFontManager()->GetFont(FontType::Normal);  // Получаем обычный шрифт
    ImFont* boldFont = FontHelper::GetBoldFont();  // Получаем жирный шрифт

    // Если активен ShowClient, меняем текст на "Packet Client"
    std::string displayText = showClientDisabled ? "Packet" : "Packet Client";

    // Настройка стиля текста
    if (boldTextDisabled) {
        ImGui::PushFont(boldFont);  // Используем жирный шрифт, если активен
    } else {
        ImGui::PushFont(regularFont);  // Используем обычный шрифт
    }

    // Применяем эффект Glow, если он включен
    if (glowEnabled) {
        ImGui::PushStyleColor(ImGuiCol_Text, themeColor);  // Яркий цвет для свечения
    } else {
        ImGui::PushStyleColor(ImGuiCol_Text, themeColor);  // Обычный цвет текста
    }

    // Отображаем текст в левом верхнем углу
    ImVec2 textPos = ImVec2(10, 10);  // Позиция текста
    ImGui::SetCursorPos(textPos);     // Устанавливаем курсор в левый верхний угол
    ImGui::Text(displayText.c_str()); // Отображаем текст

    // Показ версии проекта, если включено
    if (showVersionEnabled) {
        std::string versionText = "v3.1";  // Пример версии
        ImGui::SetCursorPos(ImVec2(10, 30));  // Смещаем курсор ниже текста
        ImGui::TextColored(ImColor(128, 128, 128), versionText.c_str()); // Отображаем серый текст для версии
    }

    // Сбрасываем стили
    if (glowEnabled) {
        ImGui::PopStyleColor();
    }

    if (boldTextDisabled) {
        ImGui::PopFont();
    }
}