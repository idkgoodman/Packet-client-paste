#pragma once
//
// Created by vastrakai on 10/10/2024.
//

#include <vector>

class MinecraftBind
{
public:
    std::string mBindName;
    std::vector<int> mBindKey;
    PAD(0x8);
};


class KeyboardMouseSettings {
public:
    PAD(0x8);
    std::vector<MinecraftBind> mKeyTypeA;
    std::vector<MinecraftBind> mKeyTypeB;

    int operator[](const std::string& key);
};

class ClientInputMappingFactory {
public:
    class KeyboardMouseSettings* getKeyboardMouseSettings();
};

class ClientInputHandler {
public:
    class ClientInputMappingFactory* getMappingFactory();
};