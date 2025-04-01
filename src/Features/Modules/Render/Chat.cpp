//
// Created by vastrakai on 9/21/2024.
//
#include "Chat.hpp"
#include <Features/Events/ChatEvent.hpp>
#include <Features/Events/PacketInEvent.hpp>
#include <SDK/Minecraft/Network/Packets/TextPacket.hpp>
#include <Utils/MiscUtils/MathUtils.hpp>
#include <SDK/Minecraft/Client/ClientInstance.hpp>
#include <Features/FeatureManager.hpp>
#include <Utils/FontHelper.hpp>
#include <Utils/MiscUtils/ImRenderUtils.hpp>
#include <Interface.hpp>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <imgui.h>

// Chat class implementation
void Chat::onEnable()
{
    gFeatureManager->mDispatcher->listen<PacketInEvent, &Chat::onPacketInEvent, nes::event_priority::ABSOLUTE_LAST>(this);
    gFeatureManager->mDispatcher->listen<RenderEvent, &Chat::onRenderEvent>(this);
}

void Chat::onDisable()
{
    gFeatureManager->mDispatcher->deafen<PacketInEvent, &Chat::onPacketInEvent>(this);
    gFeatureManager->mDispatcher->deafen<RenderEvent, &Chat::onRenderEvent>(this);
}

// Define color codes
enum class ChatColor : char {
    BLACK = '0', DARK_BLUE = '1', DARK_GREEN = '2', DARK_AQUA = '3',
    DARK_RED = '4', DARK_PURPLE = '5', GOLD = '6', GRAY = '7',
    DARK_GRAY = '8', BLUE = '9', GREEN = 'a', AQUA = 'b',
    RED = 'c', LIGHT_PURPLE = 'd', YELLOW = 'e', WHITE = 'f', RESET = 'r'
};

// Mapping of color codes to ImGui colors
static const std::unordered_map<char, ImU32> colorMap = {
    {'0', IM_COL32(0, 0, 0, 255)}, {'1', IM_COL32(0, 0, 170, 255)},
    {'2', IM_COL32(0, 170, 0, 255)}, {'3', IM_COL32(0, 170, 170, 255)},
    {'4', IM_COL32(170, 0, 0, 255)}, {'5', IM_COL32(170, 0, 170, 255)},
    {'6', IM_COL32(255, 170, 0, 255)}, {'7', IM_COL32(170, 170, 170, 255)},
    {'8', IM_COL32(85, 85, 85, 255)}, {'9', IM_COL32(85, 85, 255, 255)},
    {'a', IM_COL32(85, 255, 85, 255)}, {'b', IM_COL32(85, 255, 255, 255)},
    {'c', IM_COL32(255, 85, 85, 255)}, {'d', IM_COL32(255, 85, 255, 255)},
    {'e', IM_COL32(255, 255, 85, 255)}, {'f', IM_COL32(255, 255, 255, 255)},
    {'r', IM_COL32(255, 255, 255, 255)},  // RESET
};

// Function to get color value from map
template <typename T>
ImU32 getColorValue(const std::unordered_map<char, ImU32>& map, char code) {
    auto it = map.find(code);
    if (it != map.end()) {
        return it->second;
    }
    return IM_COL32(255, 255, 255, 255); // Default color: white
}

// Parse message into segments with color
std::vector<ParsedText> parseMessage(const std::string& message, bool isError = false) {
    std::vector<ParsedText> parsedText;
    ImU32 currentColor = IM_COL32(255, 255, 255, 255); // Default color: white
    std::string currentSegment;

    // Apply red color for error messages
    if (isError) {
        currentColor = IM_COL32(255, 85, 85, 255); // Red for errors
    }

    for (size_t i = 0; i < message.length(); ++i) {
        if (message[i] == '§') {
            if (!currentSegment.empty()) {
                ParsedText p;
                p.text = currentSegment;
                p.color = currentColor;
                parsedText.emplace_back(p);
                currentSegment.clear();
            }

            // Handle color codes
            if (i + 1 < message.length()) {
                char codeChar = std::tolower(static_cast<unsigned char>(message[i + 1]));
                auto it = colorMap.find(codeChar);
                if (it != colorMap.end()) {
                    currentColor = it->second;
                    i++; // Skip the color code character
                }
                else {
                    currentSegment += '§';
                    currentSegment += message[i + 1];
                    i++;
                }
            }
            else {
                currentSegment += '§';
            }
        }
        else {
            currentSegment += message[i];
        }
    }

    if (!currentSegment.empty()) {
        ParsedText p;
        p.text = currentSegment;
        p.color = currentColor;
        parsedText.emplace_back(p);
    }

    return parsedText;
}

// Add message to the chat with fading effect
void Chat::addMessage(std::string message, bool isError = false) {
    ChatMessage chatMessage;
    chatMessage.mText = message;
    chatMessage.mLifeTime = mMaxLifeTime.as<float>();
    chatMessage.mTime = std::chrono::system_clock::now();
    chatMessage.mPercent = 0.f;
    chatMessage.isError = isError;  // Mark error messages
    mMessages.push_back(chatMessage);
};

// GuiData class for chat window animation
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

void GuiData::animateChatOpening(float deltaTime) {
    // Chat opening animation
    if (chatOpened) {
        chatHeight += deltaTime * 200;  // Increase height over time
        if (chatHeight > 300) chatHeight = 300;  // Max height
    }
    else {
        chatHeight -= deltaTime * 200;  // Decrease height
        if (chatHeight < 0) chatHeight = 0;
    }

    // Smooth fading in of messages
    for (auto& msg : chatMessages) {
        float alpha = std::min(1.0f, msg.mPercent + deltaTime * 0.5f); // Fade in effect
        msg.mPercent = alpha;
    }
}

void GuiData::toggleChat() {
    chatOpened = !chatOpened;
}

void GuiData::displayClientMessage(const std::string& msg) {
    chatMessages.push_back(msg);
}

// Render background with transparency
void Chat::renderBackground() {
    ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.8f); // Transparent background
    ImGui::BeginChild("ChatBackground", ImVec2(0, chatHeight), false);
    ImGui::EndChild();
}

// Render chat messages with fading
void Chat::renderMessages() {
    for (auto& msg : mMessages) {
        if (msg.isError) {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 85, 85, 255)); // Red for error messages
        }
        ImGui::TextColored(ImVec4(msg.mPercent, msg.mPercent, msg.mPercent, 1.0f), "%s", msg.mText.c_str());
        if (msg.isError) {
            ImGui::PopStyleColor();
        }
    }
}
