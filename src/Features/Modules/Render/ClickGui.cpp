#include "ClickGui.hpp"
#include <Features/Events/MouseEvent.hpp>
#include <Features/Events/KeyEvent.hpp>
#include <Features/GUI/ModernDropdown.hpp>
#include <SDK/Minecraft/ClientInstance.hpp>
#include <>
#include <glm/glm.hpp>
#include <imgui.h>

#ifndef SYB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <SDK/Minecraft/Rendering/stb_image.h>
#include <SDK/Minecarft/Rendering/glfw3.h>
#include <SDK/Minecraft/Rendering/glfw3native.h>
#include <SDL.c>


static bool lastMouseState = false;
static bool isPressingShift = false;
static ModernGui modernGui = ModernGui();

void ClickGui::onEnable() {
    auto ci = ClientInstance::get();
    lastMouseState = !ci->getMouseGrabbed();
    ci->releaseMouse();

    gFeatureManager->mDispatcher->listen<MouseEvent, &ClickGui::onMouseEvent>(this);
    gFeatureManager->mDispatcher->listen<KeyEvent, &ClickGui::onKeyEvent, nes::event_priority::FIRST>(this);

    loadImage("C:\Users\Жена\Pictures\Screenshots\Снимок экрана (12).png");  // Укажите путь к изображению
}

void ClickGui::onDisable() {
    gFeatureManager->mDispatcher->deafen<MouseEvent, &ClickGui::onMouseEvent>(this);
    gFeatureManager->mDispatcher->deafen<KeyEvent, &ClickGui::onKeyEvent>(this);

    if (lastMouseState) {
        ClientInstance::get()->grabMouse();
    }

    if (buttonImageID != 0) {
        glDeleteTextures(1, &buttonImageID);  // Очистка ресурса
    }
}

void ClickGui::loadImage(const char* filePath) {
    int width, height, channels;
    unsigned char* imageData = stbi_load(filePath, &width, &height, &channels, STBI_rgb_alpha);

    if (imageData) {
        glGenTextures(1, &buttonImageID);
        glBindTexture(GL_TEXTURE_2D, buttonImageID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(imageData);
    }
}

void ClickGui::renderButton() {
    ImVec2 buttonPos = ImVec2(500, 900); // Позиция кнопки
    ImVec2 buttonSize = ImVec2(100, 50); // Размер кнопки

    if (ImGui::ImageButton((ImTextureID)(intptr_t)buttonImageID, buttonSize)) {
        isMenuOpen = !isMenuOpen;  // Переключаем меню
    }
}

void ClickGui::renderConfigMenu() {
    if (isMenuOpen) {
        ImGui::Begin("Config Menu", &isMenuOpen); // Окно меню
        ImGui::Text("Choose your configuration: ");
        if (ImGui::Button("Config 1")) {
            // Действие для первой конфигурации
        }
        if (ImGui::Button("Config 2")) {
            // Действие для второй конфигурации
        }
        if (ImGui::Button("Close")) {
            isMenuOpen = false; // Закрываем меню
        }
        ImGui::End();
    }
}

void ClickGui::onRenderEvent(RenderEvent& event) {
    if (mEnabled) ClientInstance::get()->releaseMouse();
    static float animation = 0;
    static int styleMode = 0; // Ease enum
    static int scrollDirection = 0;
    static char h[2] = { 0 };
    static EasingUtil inEase = EasingUtil();

    float delta = ImGui::GetIO().DeltaTime;

    this->mEnabled ? inEase.incrementPercentage(delta * mEaseSpeed.mValue / 10)
    : inEase.decrementPercentage(delta * 2 * mEaseSpeed.mValue / 10);
    float inScale = getEaseAnim(inEase, mAnimation.as<int>());
    if (inEase.isPercentageMax()) inScale = 0.996;
    if (mAnimation.mValue == ClickGuiAnimation::Zoom) inScale = MathUtils::clamp(inScale, 0.0f, 0.996);
    animation = MathUtils::lerp(0, 1, inEase.easeOutExpo());

    if (animation < 0.0001f) {
        return;
    }

    if (ImGui::GetIO().MouseWheel > 0) {
        scrollDirection = -1;
    }
    else if (ImGui::GetIO().MouseWheel < 0) {
        scrollDirection = 1;
    }
    else {
        scrollDirection = 0;
    }

    // Если стиль - Modern, используем этот интерфейс
    if (mStyle.mValue == ClickGuiStyle::Modern) {
        modernGui.render(animation, inScale, scrollDirection, h, mBlurStrength.mValue, mMidclickRounding.mValue, isPressingShift);
    }

    renderButton();  // Отображаем кнопку
    renderConfigMenu();  // Отображаем меню конфигов
}

void ClickGui::onMouseEvent(MouseEvent& event) {
    event.mCancelled = true;
}

void ClickGui::onKeyEvent(KeyEvent& event) {
    if (event.mKey == VK_ESCAPE) {
        if (!modernGui.isBinding && event.mPressed) this->toggle();
        event.mCancelled = true;
    }

    if (modernGui.isBinding) {
        event.mCancelled = true;
        return;
    }

    if (event.mKey == VK_SHIFT && event.mPressed) {
        isPressingShift = true;
        event.mCancelled = true;
    }
    else {
        isPressingShift = false;
    }
}