#pragma once
//
// Created by vastrakai on 7/22/2024.
//

#include <Features/Modules/Module.hpp>

class CameraComponent; // Forward declaration

class CameraClip : public ModuleBase<CameraClip> {
public:
    CameraClip() : ModuleBase<CameraClip>("CameraClip", "Disables camera clipping", ModuleCategory::Render, 0, false) {
        mNames = {
            {Lowercase, "cameraclip"},
            {LowercaseSpaced, "camera clip"},
            {Normal, "CameraClip"},
            {NormalSpaced, "Camera Clip"}
        };
    }

    void onEnable() override;
    void onDisable() override;
};