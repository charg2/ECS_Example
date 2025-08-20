module;

#include <entt/entt.hpp>

export module Pc;

import EntityObject;

export class Pc final : public WorldObject
{
public:
    Pc() = default;
    Pc( entt::entity entity );

    ~Pc() final = default;
};

Pc::Pc( entt::entity entity )
: WorldObject{ entity }
{
}


export using PcPtr = std::shared_ptr< Pc >;



class Npc final : public WorldObject
{
public:
    Npc() = default;
    Npc( entt::entity entity )
    : WorldObject{ entity }
    {
    }
    ~Npc() final = default;
};

using NpcPtr = std::shared_ptr< Npc >;
