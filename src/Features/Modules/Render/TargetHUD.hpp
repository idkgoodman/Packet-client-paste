#ifndef TARGETHUD_HPP
#define TARGETHUD_HPP

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <imgui.h>
#include <ImColor.h>
#include <PacketInEvent.hpp>
#include <PlayerAuthInputPacket.hpp>
#include <ColorUtils.hpp>

class TargetHUD {
public:
    ImVec2 position;
    bool isActive = false;
    bool isBeingDragged = false;
    ImVec2 dragOffset;
    float targetTiltAngle = 0.0f;  // Угол наклона головы
    float vignetteAlpha = 0.0f;    // Прозрачность красной виньетки

    TargetHUD();

    void StartDrag(ImVec2 mousePos);
    void StopDrag();
    void UpdateDrag(ImVec2 mousePos);
    void onPacketInEvent(PacketInEvent& event);
    void onRenderEvent();
    void Render(float playerHealth, const std::string& playerName, const ImVec2& playerHeadPos, ImTextureID playerHeadTexture);
    void RenderHPBar(float health);
    void spawnParticles(glm::vec2 playerHeadPos);
    void updateParticles(float deltaTime);
    void drawParticles();

private:
    std::vector<Particle> particles; // Вектор для хранения частиц
    glm::vec4 themeColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // Цвет темы (например, красный)

    // Структура для частиц
    struct Particle {
        glm::vec2 position; // Позиция частицы
        glm::vec2 velocity; // Направление и скорость
        glm::vec4 color;    // Цвет
        float lifeTime;     // Время жизни
        float maxLifeTime;  // Максимальное время жизни
    };

    // Случайное число в заданном диапазоне
    float randFloat(float min, float max);
};

#endif // TARGETHUD_HPP