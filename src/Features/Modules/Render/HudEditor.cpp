//
// Created by vastrakai on 9/14/2024.
//

#include "HudEditor.hpp"
#include <imgui.h>
#include <ClientInstance.hpp>

// Проверка, открыт ли чат
bool isChatOpen() {
    return ClientInstance::get()->getChat()->isChatOpen();  // Заменить на реальный метод проверки состояния чата
}

void DraggableElement::draw() {
    ImVec2 min = ImVec2(mPosX, mPosY);
    ImVec2 max = ImVec2(mPosX + mWidth, mPosY + mHeight);

    // Если HUD Editor активен и чат открыт, рисуем рамку и делаем элемент интерактивным
    if (HudEditor::getInstance().isEditorActive() && isChatOpen() && ImGui::IsMouseHoveringRect(min, max)) {
        // Рисуем полупрозрачный фон с белесым оттенком
        ImGui::GetWindowDrawList()->AddRectFilled(min, max, IM_COL32(255, 255, 255, 40));

        // Рисуем белую рамку вокруг элемента
        ImGui::GetWindowDrawList()->AddRect(min, max, IM_COL32(255, 255, 255, 255), 5.0f);

        // Начинаем перетаскивание, если кликнули на элемент
        if (ImGui::IsMouseClicked(0)) {
            mIsDragging = true;
        }

        // Перетаскивание элемента
        if (mIsDragging) {
            ImVec2 mousePos = ImGui::GetIO().MousePos;
            mPosX = mousePos.x - mWidth / 2.0f;
            mPosY = mousePos.y - mHeight / 2.0f;

            // Завершаем перетаскивание, если отпустили кнопку мыши
            if (ImGui::IsMouseReleased(0)) {
                mIsDragging = false;
            }
        }
    }

    // Отображаем сам элемент (например, текст или кнопку)
    ImGui::Text(mLabel.c_str());
}
