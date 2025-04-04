#ifndef MCP_HPP
#define MCP_HPP

#include <Module.hpp>
#include <Actor.hpp>
#include <HitResult.hpp>
#include <Friend.hpp>
#include <ItemUtils.hpp>
#include <ChatUtils.hpp>

class MCP : public ModuleBase<MCP> {
public:
    MCP(); // Конструктор
    ~MCP(); // Деструктор

    void onMidClickHitEntity(Actor* player, const HitResult* hitResult);

    // Имя модуля
    const std::map<std::string, std::string> mNames = {
        {"Lowercase", "mcp"},
        {"LowercaseSpaced", "mcp"},
        {"Normal", "MCP"},
        {"NormalSpaced", "MCP"}
    };


private:
    bool mAddFriend; // Флаг для добавления друга
    bool mThrowPearl; // Флаг для использования Ender Pearl
    bool mHotbarOnly; // Флаг, если нужно использовать только предметы на хотбаре
    bool mThrowNextTick; // Флаг для использования Ender Pearl в следующем тике

    void useEnderPearl(Actor* player);
};

#endif // MCP_HPP