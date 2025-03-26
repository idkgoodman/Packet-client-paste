#pragma once

#include "Features/Modules/Module.hpp"
#include "Features/Events/RenderEvent.hpp"
#include "imgui.h"
#include <memory>
#include "glm/glm.hpp"
#include "HudEditor.hpp"

class HPBar : public ModuleBase<HPBar> {
public:
    HPBar() : ModuleBase("HP Bar", "Displays player's health in a custom HUD", ModuleCategory::Visual, 0, false) {
        mNames = {
            {Lowercase, "hpbar"},
            {LowercaseSpaced, "hp bar"},
            {Normal, "HPBar"},
            {NormalSpaced, "HP Bar"}
        };

        mElement = std::make_unique<HudElement>();
        mElement->mPos = { 10, 10 }; // Начальная позиция
        mElement->mAnchor = HudElement::Anchor::BottomLeft;
        const char* ModuleBaseType = ModuleBase<HPBar>::getTypeID();
        mElement->mParentTypeIdentifier = const_cast<char*>(ModuleBaseType);
        mElement->mSize = glm::vec2(100, 10); // Размер полоски здоровья
        HudEditor::gInstance->registerElement(mElement.get());
    }

    void onEnable() override;
    void onDisable() override;
    void onRenderEvent(RenderEvent& event);

private:
    std::unique_ptr<HudElement> mElement = nullptr;
};