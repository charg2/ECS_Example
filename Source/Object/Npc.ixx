export module Npc;

import WorldObject;

export class Npc final : public WorldObject
{
public:
    Npc() = default;
    Npc( entt::entity entity )
    : WorldObject{ entity }
    {
    }

    ~Npc() final = default;
};

export using NpcPtr = std::shared_ptr< Npc >;
