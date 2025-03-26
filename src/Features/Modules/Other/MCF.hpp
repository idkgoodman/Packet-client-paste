// MCF.hpp
#ifndef MCF_HPP
#define MCF_HPP

#include <Actor.hpp>
#include <ActorOwnerComponent.hpp>
#include <ActorTypeComponent.hpp>
#include <RuntimeIDComponent.hpp>
#include <Friend.hpp>
#include <HitResult.hpp>
#include <Module.hpp>

class MCF : public ModuleBase<MCF> {
public:
    MCF(); // Конструктор
    ~MCF(); // Деструктор

    void onMidClickHitEntity(Actor* player, const HitResult* hitResult);
    void addFriend(Actor* target);
    void removeFriend(Actor* target);

    // Имя модуля
    const std::map<std::string, std::string> mNames = {
        {"Lowercase", "mcf"},
        {"LowercaseSpaced", "mcf"},
        {"Normal", "MCF"},
        {"NormalSpaced", "MCF"}
    };

private:
    bool mAddFriend; // Флаг для добавления друга
    bool mRemoveFriend; // Флаг для удаления друга
};

#endif // MCF_HPP