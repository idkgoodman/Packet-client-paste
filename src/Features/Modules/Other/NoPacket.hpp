#pragma once
//
// Created by vastrakai on 7/19/2024.
//

#include <Module.hpp>


class NoPacket : public ModuleBase<NoPacket> {
public:
    BoolSetting mMoveOnly = BoolSetting("Move Only", "Only cancel movement packets", false);

    NoPacket() : ModuleBase("NoPacket", "Prevents packets from being sent to the server", ModuleCategory::Other, 0, false)
    {
        addSetting(&mMoveOnly);

        mNames = {
            {Lowercase, "nopacket"},
            {LowercaseSpaced, "no packet"},
            {Normal, "NoPacket"},
            {NormalSpaced, "No Packet"}
        };
    }

    void onEnable() override;
    void onDisable() override;
    void onPacketOutEvent(class PacketOutEvent& event) const;

};