#include "AimAssist.hpp"
#include "SDK/Minecraft/World/Level.hpp"
#include "Utils/MathUtils.hpp"
#include <ClientInstance.hpp>
#include <FeatureManager.hpp>
#include <Actor.hpp>
#include <Level.hpp>
#include <glm/glm.hpp>

void AimAssist::onEnable() {
    {
        mElement->mVisible = true;
    }

void AimAssist::onDisable() {
    {
        mElement->mVisible = false;
    }



void AimAssist::onBaseTickEvent(BaseTickEvent& event) {
    auto player = ClientInstance::get()->getLocalPlayer();
    if (!player || player->isDead()) return;

    Player* target = getClosestTarget();
    if (target) aimAtTarget(target);
}

Player* AimAssist::getClosestTarget() {
    auto player = ClientInstance::get()->getLocalPlayer();
    if (!player) return nullptr;

    auto level = ClientInstance::get()->getLevel();
    if (!level) return nullptr;

    Player* closest = nullptr;
    float closestDistance = maxDistance.mValue;

    for (auto& entity : level->getPlayers()) {
        if (!entity || entity->isDead() || entity == player) continue;

        float distance = glm::distance(player->getPosition(), entity->getPosition());
        if (distance < closestDistance) {
            glm::vec3 lookVec = player->getLookVec();
            glm::vec3 toTarget = glm::normalize(entity->getPosition() - player->getPosition());

            float angle = glm::degrees(acos(glm::dot(lookVec, toTarget)));
            if (angle < fov.mValue) {
                closest = entity;
                closestDistance = distance;
            }
        }
    }
    return closest;
}

void AimAssist::aimAtTarget(Player* target) {
    auto player = ClientInstance::get()->getLocalPlayer();
    if (!player || !target) return;

    glm::vec3 playerPos = player->getPosition();
    glm::vec3 targetPos = target->getPosition();

    glm::vec2 currentYawPitch = player->getYawPitch();
    glm::vec2 targetYawPitch = MathUtils::calculateAngle(playerPos, targetPos);

    glm::vec2 newYawPitch = glm::mix(currentYawPitch, targetYawPitch, smoothness.mValue);

    player->setYawPitch(newYawPitch);
}