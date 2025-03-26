#ifndef CHAT_HPP
#define CHAT_HPP

#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>
#include <imgui.h>
#include <Module.hpp>
#include <PacketInEvent.hpp>
#include <RenderEvent.hpp>


// Forward declarations
class ChatMessage;
class GuiData;

class Chat : public ModuleBase<Chat> {
public:
    Chat()
        : ModuleBase<Chat>("Chat", "A Packet-themed chat (i hate this)", ModuleCategory::Render, 0, false) {
        mNames = {
            {Lowercase, "chat"},
            {LowercaseSpaced, "chat"},
            {Normal, "Chat"},
            {NormalSpaced, "Chat"}
        };
    }

    // Конструктор и деструктор
    ~Chat() = default;

    // Методы для включения/выключения
    void onEnable() override;
    void onDisable() override;

    // Метод для добавления сообщений в чат
    void addMessage(std::string message);

private:
    // Метод для обработки входящих пакетов
    void onPacketInEvent(const PacketInEvent& event);

    // Метод для рендеринга чата
    void onRenderEvent(const RenderEvent& event);

    // Структура для хранения информации о сообщении чата
    struct ChatMessage {
        std::string mText;
        std::chrono::system_clock::time_point mTime;
        float mLifeTime;
        float mPercent;
    };

    std::vector<ChatMessage> mMessages; // Список сообщений чата
    float mMaxLifeTime = 10.0f;         // Максимальное время жизни сообщения
};

// Структуры и функции для парсинга текста чата с цветами
struct ParsedText {
    std::string text;
    ImVec2 pos;
    ImU32 color;
};

enum class ChatColor : char {
    BLACK = '0',
    DARK_BLUE = '1',
    DARK_GREEN = '2',
    DARK_AQUA = '3',
    DARK_RED = '4',
    DARK_PURPLE = '5',
    GOLD = '6',
    GRAY = '7',
    DARK_GRAY = '8',
    BLUE = '9',
    GREEN = 'a',
    AQUA = 'b',
    RED = 'c',
    LIGHT_PURPLE = 'd',
    YELLOW = 'e',
    WHITE = 'f'
};

static const std::unordered_map<char, ImU32> colorMap = {
    {'0', IM_COL32(0, 0, 0, 255)},
    {'1', IM_COL32(0, 0, 170, 255)},
    {'2', IM_COL32(0, 170, 0, 255)},
    {'3', IM_COL32(0, 170, 170, 255)},
    {'4', IM_COL32(170, 0, 0, 255)},
    {'5', IM_COL32(170, 0, 170, 255)},
    {'6', IM_COL32(255, 170, 0, 255)},
    {'7', IM_COL32(170, 170, 170, 255)},
    {'8', IM_COL32(85, 85, 85, 255)},
    {'9', IM_COL32(85, 85, 255, 255)},
    {'a', IM_COL32(85, 255, 85, 255)},
    {'b', IM_COL32(85, 255, 255, 255)},
    {'c', IM_COL32(255, 85, 85, 255)},
    {'d', IM_COL32(255, 85, 255, 255)},
    {'e', IM_COL32(255, 255, 85, 255)},
    {'f', IM_COL32(255, 255, 255, 255)},
    {'r', IM_COL32(255, 255, 255, 255)},
};

template <typename T>
ImU32 getColorValue(const std::unordered_map<char, ImU32>& map, char code);

std::vector<ParsedText> parseMessage(const std::string& message);

class GuiData {
public:
    void animateChatOpening(float deltaTime);
    void toggleChat();
    void displayClientMessage(const std::string& msg);

private:
    bool chatOpened = false;
    float chatHeight = 0.0f;
    float chatWidth = 0.0f;
    float inputHeight = 0.0f;
    std::vector<std::string> chatMessages;
    float GuiScale = 1.0f;
};

#endif // CHAT_HPP