//
// Created by Жена on 22.03.2025.
//

#include <MCF.hpp>
#include <ActorOwnerComponent.hpp>
#include <RuntimeIDComponent.hpp>
#include <Actor.hpp>
#include <ActorType.hpp>
#include <ActorTypeComponent.hpp>
#include <Friend.hpp>
#include <ChatUtils.hpp>

if (hitResult->mType == ENTITY && mAddFriend.mValue)
{
    auto entity = hitResult->mEntity.id;
    Actor* target = nullptr;
    for (auto&& [id, moduleOwner, type, ridc] : player->mContext.mRegistry->view<ActorOwnerComponent, ActorTypeComponent, RuntimeIDComponent>().each()) {
        if (type.mType != ActorType::Player) continue;
        if (id == entity) {
            target = moduleOwner.mActor;
            break;
        }
    }

    if (target)
    {
        bool isFriend = gFriendManager->isFriend(target);
        if (isFriend)
        {
            gFriendManager->removeFriend(target);
        }
        else
        {
            gFriendManager->addFriend(target);
        }

        ChatUtils::displayClientMessage(!isFriend ? "§aAdded " + target->getRawName() + " to your friends list!" : "§cRemoved " + target->getRawName() + " from your friends list!");
    }
}
