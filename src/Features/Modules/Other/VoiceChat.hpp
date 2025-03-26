#pragma once
//
// Created by vastrakai on 10/16/2024.
//

#include <Module.hpp>



class VoiceChat : public ModuleBase<VoiceChat> {
public:
    VoiceChat() : ModuleBase("VoiceChat", "Voice chat for the game", ModuleCategory::Other, 0, false) {
        mNames = {
            {Lowercase, "voicechat"},
            {LowercaseSpaced, "voice chat"},
            {Normal, "VoiceChat"},
            {NormalSpaced, "Voice Chat"}
        };
    }

    void onEnable() override;
    void onDisable() override;
    void onInit() override;

};