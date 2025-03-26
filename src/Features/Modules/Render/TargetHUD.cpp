#include <imgui.h>
#include <string>
#include <sstream>
#include <HudEditor.hpp>
#include <PacketInEvent.hpp>
#include <MathUtils.hpp>
#include <PacketID.hpp>
#include <PlayerAuthInputPacket.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <cstdlib>
#include <Interface.hpp>
#include <ColorUtils.hpp>
#include <glfw3.h>  // If you're using GLFW for window/context management

class TargetHUD {
public:
    ImVec2 position;
    bool isActive = false;
    bool isBeingDragged = false;
    ImVec2 dragOffset;
    float targetTiltAngle = 0.0f; // Угол наклона головы
    float vignetteAlpha = 0.0f;   // Прозрачность красной виньетки

    void StartDrag(ImVec2 mousePos) {
        isBeingDragged = true;
        dragOffset = position - mousePos;
    }

    void StopDrag() {
        isBeingDragged = false;
    }

    void UpdateDrag(ImVec2 mousePos) {
        if (isBeingDragged) {
            position = mousePos + dragOffset;
        }
    }

    void onPacketInEvent(PacketInEvent& event) {
        if (event.mPacket->getId() == PacketID::PlayerAuthInput) {
            auto paip = event.getPacket<PlayerAuthInputPacket>();

            if (paip->mIsAttacking) {
                targetTiltAngle = -10.0f; // Голова наклоняется
                vignetteAlpha = 1.0f;     // Виньетка полностью проявляется
            }
        }
    }

    void onRenderEvent() {
        float lerpSpeed = 10.0f;
        targetTiltAngle = MathUtils::lerp(targetTiltAngle, 0.0f, ImGui::GetIO().DeltaTime * lerpSpeed);
        vignetteAlpha = MathUtils::lerp(vignetteAlpha, 0.0f, ImGui::GetIO().DeltaTime * lerpSpeed);
    }

    void Render(float playerHealth, const std::string& playerName, const ImVec2& playerHeadPos, ImTextureID playerHeadTexture) {
        if (!isActive) return;

        ImGui::GetWindowDrawList()->AddRectFilled(position, position + ImVec2(200, 50), ImColor(0, 0, 0, 200), 10.0f);

        // Рисуем голову игрока с наклоном
        ImVec2 headCenter = ImVec2(position.x + 25, position.y + 25);
        ImGui::GetWindowDrawList()->AddImageRotated(playerHeadTexture, headCenter, ImVec2(32, 32), targetTiltAngle);

        // Рисуем красную виньетку вокруг головы
        if (vignetteAlpha > 0.01f) {
            ImGui::GetWindowDrawList()->AddCircle(headCenter, 20, ImColor(255, 0, 0, static_cast<int>(vignetteAlpha * 255)), 32, 4.0f);
        }

        // Render player name
        ImGui::GetWindowDrawList()->AddText(ImVec2(position.x + 50, position.y + 10), ImColor(255, 255, 255), playerName.c_str());

        // Render HP Bar
        RenderHPBar(playerHealth);

        // Spawn and update particles
        spawnParticles(playerHeadPos);
        updateParticles(ImGui::GetIO().DeltaTime);
        drawParticles();
    }

    void RenderHPBar(float health) {
        float hpWidth = (health / 30.0f) * 100.0f;
        ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(position.x + 50, position.y + 30), ImVec2(position.x + 50 + hpWidth, position.y + 40), ImColor(255, 255, 0), 5.0f);
    }

private:
    struct Particle {
        glm::vec2 position; // Позиция частицы
        glm::vec2 velocity; // Направление и скорость
        glm::vec4 color;    // Цвет
        float lifeTime;     // Время жизни
        float maxLifeTime;  // Максимальное время жизни
    };

    std::vector<Particle> particles; // Вектор для хранения частиц
    glm::vec4 themeColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // Цвет темы (например, красный)

    // Случайное число в заданном диапазоне
    float randFloat(float min, float max) {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }

    void spawnParticles(glm::vec2 playerHeadPos) {
        int numParticles = 10; // Количество частиц
        for (int i = 0; i < numParticles; ++i) {
            Particle p;
            p.position = playerHeadPos; // Начальная позиция — это позиция головы игрока
            p.velocity = glm::vec2(randFloat(-1.0f, 1.0f), randFloat(-1.0f, 1.0f)); // Случайное направление
            p.velocity *= randFloat(10.0f, 20.0f); // Масштабирование по дальности
            p.color = themeColor; // Цвет частицы (цвет темы)
            p.lifeTime = 0.0f;
            p.maxLifeTime = randFloat(0.5f, 1.0f); // Время жизни от 0.5 до 1 секунды

            particles.push_back(p); // Добавление частицы в систему
        }
    }

    void updateParticles(float deltaTime) {
        for (auto it = particles.begin(); it != particles.end();) {
            it->lifeTime += deltaTime; // Увеличение времени жизни

            if (it->lifeTime > it->maxLifeTime) {
                it = particles.erase(it); // Удаление старых частиц
            } else {
                it->position += it->velocity * deltaTime; // Обновление позиции
                it->color.a = 1.0f - (it->lifeTime / it->maxLifeTime); // Уменьшение прозрачности

                ++it; // Переход к следующей частице
            }
        }
    }

    void drawParticles() {
        for (const auto& p : particles) {
            glBegin(GL_POINTS);
            glColor4f(p.color.r, p.color.g, p.color.b, p.color.a); // Используем цвет частицы
            glVertex2f(p.position.x, p.position.y);
            glEnd();
        }
    }
};