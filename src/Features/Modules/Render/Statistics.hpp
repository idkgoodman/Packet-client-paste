//
// Created by alteik on 02/10/2024.
//
#pragma once

#include "HudEditor.hpp"
#include <Module.hpp>

class Statistics : public ModuleBase<Stistics> {
public:
    Statistics() : ModuleBase("Statistics", "Displays info about your current session!", ModuleCategory::Render, 0, false) {
        mNames = {
                {Lowercase, "statistics"},
                {LowercaseSpaced, "statistics"},
                {Normal, "Statistics"},
                {NormalSpaced, "Statistics"},
        };

        mElement = std::make_unique<HudElement>();
        mElement->mPos = { 10, 0 };
        mElement->mAnchor = HudElement::Anchor::MiddleLeft;
        const char* ModuleBaseType = ModuleBase<Statistics>::getTypeID();;
        mElement->mParentTypeIdentifier = const_cast<char*>(ModuleBaseType);
        mElement->mSize = glm::vec2(200, 105);
        HudEditor::gInstance->registerElement(mElement.get());
    }

    std::unique_ptr<HudElement> mElement = nullptr;

    static void onHttpResponse(HttpResponseEvent event);
    void makeRequestsForAllGamemodes(const std::string& gamertag);
    std::vector<std::pair<uint64_t, std::unique_ptr<HttpRequest>>> mRequests;
    std::string mPlayerName = "";
    void resetStatistics();
    uint64_t lastUpdate = 0;

    int style = 0;

    float siY = 350;
    float siX = 10;

    float alphaAnim = 1.f;

    void onEnable() override;
    void onDisable() override;
    void onRenderEvent(class RenderEvent& event);
    void onBaseTickEvent(class BaseTickEvent& event);
};