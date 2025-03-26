//
// Created by vastrakai on 7/2/2024.
//

#include "NoSlow.hpp"

#include <Features/FeatureManager.hpp>
#include <SDK/Minecraft/ClientInstance.hpp>
#include <SDK/Minecraft/Actor/Actor.hpp>

std::vector<unsigned char> gNsBytes = { 0xC3, 0x90, 0x90, 0x90 ,0x90 };
DEFINE_PATCH_FUNC(NoSlow::patchSlow, SigManager::tickEntity_ItemUseSlowdownModifierComponent, gNsBytes);

void NoSlow::onEnable()
{
    gFeatureManager->mDispatcher->listen<BaseTickEvent, &NoSlow::onBaseTickEvent>(this);
    patchSlowdown(true);
}

void NoSlow::onDisable()
{
    gFeatureManager->mDispatcher->deafen<BaseTickEvent, &NoSlow::onBaseTickEvent>(this);
    patchSlowdown(false);
}

void NoSlow::onBaseTickEvent(BaseTickEvent& event)
{
    auto player = ClientInstance::get()->getLocalPlayer();

    auto slowdownComponent = player->getBlockMovementSlowdownMultiplierComponent();

    slowdownComponent->mBlockMovementSlowdownMultiplier = glm::vec3(0.f, 0.f, 0.f);
}