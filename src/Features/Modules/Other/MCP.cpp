//
// Created by Жена on 22.03.2025.
//

#include "MCP.hpp"
#include <spdlog/spdlog.h>
#include <HitResult.hpp>
#include <ItemStack.hpp>


MCP::MCP() : mThrowPearl(true), mHotbarOnly(true), mThrowNextTick(false) {}

MCP::~MCP() {}

void MCP::onMidClickHitEntity(Actor* player, const HitResult* hitResult) {
    if (ClientInstance::get()->getMouseGrabbed()) return;

    int slot = -1;
    // Поиск Ender Pearl в инвентаре
    for (int i = 0; i < 36; i++) {
        auto itemStack = player->getSupplies()->getContainer()->getItem(i);
        if (!itemStack) continue;
        if (!itemStack->mItem) continue;

        auto item = itemStack->getItem();
        if (item->mName == "ender_pearl") {
            slot = i;
            break;
        }
    }

    if (mHotbarOnly && slot > 8) slot = -1; // Если только для хотбара, игнорируем предметы на других слотах

    // Используем Ender Pearl, если она есть
    if (mThrowNextTick && slot != -1) {
        mThrowNextTick = false;
        ItemUtils::useItem(slot); // Используем предмет
        spdlog::info("Used ender pearl!");
    }

    static bool lastMidClick = false;
    bool midClick = ImGui::IsMouseDown(2);

    if (midClick && !lastMidClick) {
        spdlog::info("Midclick!");

        auto hitResult = player->getLevel()->getHitResult();
        if (hitResult->mType == ENTITY && mAddFriend) { // Если клик по игроку
            auto entity = hitResult->mEntity.id;
            Actor* target = nullptr;
            for (auto&& [id, moduleOwner, type, ridc] : player->mContext.mRegistry->view<ActorOwnerComponent, ActorTypeComponent, RuntimeIDComponent>().each()) {
                if (type.mType != ActorType::Player) continue;
                if (id == entity) {
                    target = moduleOwner.mActor;
                    break;
                }
            }

            if (target) {
                bool isFriend = gFriendManager->isFriend(target);
                if (isFriend) {
                    gFriendManager->removeFriend(target); // Убираем из друзей
                    ChatUtils::displayClientMessage("§cRemoved " + target->getRawName() + " from your friends list!");
                } else {
                    gFriendManager->addFriend(target); // Добавляем в друзья
                    ChatUtils::displayClientMessage("§aAdded " + target->getRawName() + " to your friends list!");
                }
            }
        }
    }

    lastMidClick = midClick;
}