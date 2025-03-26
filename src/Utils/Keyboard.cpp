//
// Created by vastrakai on 6/29/2024.
//

#include "Keyboard.hpp"

#include <SDK/Minecraft/ClientInstance.hpp>
#include <SDK/Minecraft/KeyboardMouseSettings.hpp>
#include <SDK/Minecraft/Actor/Actor.hpp>
#include <SDK/Minecraft/Actor/Components/MoveInputComponent.hpp>

#include "StringUtils.hpp"

int Keyboard::getKeyId(const std::string& str)
{
    std::string lowerStr = StringUtils::toLower(str);
    if (mKeyMap.find(lowerStr) != mKeyMap.end()) {
        return mKeyMap[lowerStr];
    }
    return -1; // Возвращаем -1, если ключ не найден
}

bool Keyboard::isUsingMoveKeys(bool includeSpaceShift)
{
    auto player = ClientInstance::get()->getLocalPlayer();
    if (!player) return false;

    auto keyboardSettings = ClientInstance::get()->getKeyboardSettings();
    if (!keyboardSettings) return false;

    auto moveInput = player->getMoveInputComponent();
    if (!moveInput) return false;

    bool isMoving = moveInput->mForward || moveInput->mBackward || moveInput->mLeft || moveInput->mRight;
    if (includeSpaceShift)
    {
        int jumpKey = keyboardSettings->getMapping("key.jump");
        int sneakKey = keyboardSettings->getMapping("key.sneak");
        return isMoving || mPressedKeys[jumpKey] || mPressedKeys[sneakKey];
    }

    return isMoving;
}

bool Keyboard::isStrafing()
{
    auto player = ClientInstance::get()->getLocalPlayer();
    if (!player) return false;

    auto moveInput = player->getMoveInputComponent();
    if (!moveInput) return false;

    return moveInput->mLeft || moveInput->mRight || moveInput->mBackward;
}

// Возвращает строковое представление клавиши
std::string Keyboard::getKey(int keyId)
{
    for (const auto& [key, value] : mKeyMap)
    {
        if (value == keyId)
        {
            return StringUtils::toUpper(key);
        }
    }

    return "UNKNOWN"; // Явно указываем неизвестный ключ
}