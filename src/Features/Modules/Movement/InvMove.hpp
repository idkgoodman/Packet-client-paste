#pragma once
//
// Created by vastrakai on 7/12/2024.
//

#include <Features/Modules/Module.hpp>

class InvMove : public ModuleBase<InvMove> {
public:
    BoolSetting mDisallowShift = BoolSetting("Disallow Sneaking", "Disallows sneaking while in inventory.", false);

    InvMove() : ModuleBase("InvMove", "Allows you to move while your inventory is open.", ModuleCategory::Movement, 0, false) {
        addSettings(&mDisallowShift);

        mNames = {
            {Lowercase, "invmove"},
            {LowercaseSpaced, "inv move"},
            {Normal, "InvMove"},
            {NormalSpaced, "Inv Move"}
        };
    }

    bool mHasOpenContainer = false;

    static void patchFunc1(bool);
    static void patchFunc2(bool);
    static void patchFunc(bool b)
    {
        patchFunc1(b);
        patchFunc2(b);
    }
    void onEnable() override;
    void onDisable() override;
    void onBaseTickEvent(class BaseTickEvent& event);
    void onRenderEvent(class RenderEvent& event);
    void onPacketInEvent(class PacketInEvent& event);
    void onPacketOutEvent(class PacketOutEvent& event);
};